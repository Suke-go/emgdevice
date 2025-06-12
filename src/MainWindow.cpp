#include "MainWindow.hpp"
#include "SerialCommunicator.hpp"
#include "DataProcessor.hpp"
#include "CSVLogger.hpp"
#include <ctime>
#include <type_traits>
#if __has_include(<imgui.h>)
#  include <imgui.h>
#else
struct ImVec2 { float x; float y; };
struct ImVec4 { float x, y, z, w; ImVec4(float a=0, float b=0, float c=0, float d=0)
        : x(a), y(b), z(c), w(d) {}
};
namespace ImGui {
inline void Begin(const char*) {}
inline void End() {}
inline bool SliderInt(const char*, int*, int, int) { return false; }
inline bool Button(const char*) { return false; }
inline void PushStyleColor(int, int) {}
inline void PopStyleColor() {}
inline ImVec2 GetMousePos() { return ImVec2{0,0}; }
using ImGuiID = unsigned int;
inline ImGuiID GetID(const char*) { return 0; }
}
#endif

#if __has_include(<implot.h>)
#  include <implot.h>
#else
namespace ImPlot {
inline bool BeginPlot(const char*) { return true; }
inline void EndPlot() {}
inline void PlotLine(const char*, const float*, int) {}
using ImVec4 = ::ImVec4;
enum ImPlotDragToolFlags_ { ImPlotDragToolFlags_None = 0 };
using ImPlotDragToolFlags = int;
inline bool DragLineX(const char*, double*, bool = true) { return false; }
inline bool DragLineX(int, double*, const ImVec4& = ImVec4(), float = 1.0f,
                      ImPlotDragToolFlags = ImPlotDragToolFlags_None,
                      bool* = nullptr, bool* = nullptr, bool* = nullptr) {
    return false;
}
}
#endif

namespace {
template <typename, typename = void>
struct has_old_draglinex_impl : std::false_type {};
template <typename Dummy>
struct has_old_draglinex_impl<
    Dummy,
    std::void_t<decltype(ImPlot::DragLineX("", (double*)nullptr, true))>>
    : std::true_type {};
constexpr bool has_old_draglinex = has_old_draglinex_impl<void>::value;

template <typename, typename = void>
struct has_new_draglinex_impl : std::false_type {};
template <typename Dummy>
struct has_new_draglinex_impl<
    Dummy,
    std::void_t<decltype(ImPlot::DragLineX(
        0,
        (double*)nullptr,
        ::ImVec4{},
        1.0f,
        0,
        (bool*)nullptr,
        (bool*)nullptr,
        (bool*)nullptr))>> : std::true_type {};
constexpr bool has_new_draglinex = has_new_draglinex_impl<void>::value;
}

MainWindow::MainWindow(SerialCommunicator& serial,
                       DataProcessor& processor,
                       CSVLogger& logger)
    : serial_(serial), processor_(processor), logger_(logger) {
    markerStart_ = 0.0;
    markerEnd_ = static_cast<double>(processor_.windowSize());
}

void MainWindow::render() {
    ImGui::Begin("EMG Control");

    int winSize = static_cast<int>(processor_.windowSize());
    if (ImGui::SliderInt("Window Size", &winSize, 1, 1024)) {
        processor_.setWindowSize(static_cast<size_t>(winSize));
        markerEnd_ = markerStart_ + winSize;
    }

    winSize = static_cast<int>(processor_.windowSize());
    int overlap = static_cast<int>(processor_.overlap());
    if (ImGui::SliderInt("Overlap", &overlap, 0, winSize - 1)) {
        processor_.setOverlap(static_cast<size_t>(overlap));
    }

    const std::vector<float>& raw = processor_.raw();
    const std::vector<float>& rms = processor_.processed();

    if (ImPlot::BeginPlot("EMG")) {
        if (!raw.empty()) {
            ImPlot::PlotLine("Raw", raw.data(), static_cast<int>(raw.size()));
        }
        if (!rms.empty()) {
            ImPlot::PlotLine("RMS", rms.data(), static_cast<int>(rms.size()));
        }

        // Support both old and new ImPlot signatures for DragLineX.
        if constexpr (has_new_draglinex) {
            ImPlot::DragLineX(ImGui::GetID("Start"), &markerStart_,
                              ImVec4(1, 0, 0, 1), 1.0f,
                              0, nullptr, nullptr, nullptr);
            ImPlot::DragLineX(ImGui::GetID("End"), &markerEnd_,
                              ImVec4(0, 1, 0, 1), 1.0f,
                              0, nullptr, nullptr, nullptr);
        } else if constexpr (has_old_draglinex) {
            ImPlot::DragLineX("Start", &markerStart_, true);
            ImPlot::DragLineX("End", &markerEnd_, true);
        }

        ImPlot::EndPlot();
    }

    if (markerEnd_ < markerStart_) {
        double tmp = markerStart_;
        markerStart_ = markerEnd_;
        markerEnd_ = tmp;
    }
    size_t dragged = static_cast<size_t>(markerEnd_ - markerStart_);
    if (dragged == 0) {
        dragged = 1;
    }
    if (dragged != processor_.windowSize()) {
        processor_.setWindowSize(dragged);
    }

    if (recording_) {
        ImGui::PushStyleColor(0, 0xff0000);
    }
    if (ImGui::Button(recording_ ? u8"\u25A0 Stop" : u8"\u25CF Record")) {
        recording_ = !recording_;
        if (recording_) {
            std::time_t t = std::time(nullptr);
            std::tm tm{};
#ifdef _WIN32
            localtime_s(&tm, &t);
#else
            localtime_r(&t, &tm);
#endif
            char buf[64];
            std::strftime(buf, sizeof(buf), "EMG_data_%Y-%m-%d_%H-%M-%S.csv", &tm);
            logger_.open(buf);
        } else {
            logger_.close();
        }
    }
    if (recording_) {
        ImGui::PopStyleColor();
    }

    ImGui::End();
}
