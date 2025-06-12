#include "MainWindow.hpp"
#include "SerialCommunicator.hpp"
#include "DataProcessor.hpp"
#include "CSVLogger.hpp"
#if __has_include(<imgui.h>)
#  include <imgui.h>
#else
namespace ImGui {
inline void Begin(const char*) {}
inline void End() {}
inline bool SliderInt(const char*, int*, int, int) { return false; }
}
#endif

#if __has_include(<implot.h>)
#  include <implot.h>
#else
namespace ImPlot {
inline bool BeginPlot(const char*) { return true; }
inline void EndPlot() {}
inline void PlotLine(const char*, const float*, int) {}
}
#endif

MainWindow::MainWindow(SerialCommunicator& serial,
                       DataProcessor& processor,
                       CSVLogger& logger)
    : serial_(serial), processor_(processor), logger_(logger) {}

void MainWindow::render() {
    ImGui::Begin("EMG Control");

    int winSize = static_cast<int>(processor_.windowSize());
    if (ImGui::SliderInt("Window Size", &winSize, 1, 1024)) {
        processor_.setWindowSize(static_cast<size_t>(winSize));
    }

    int overlap = static_cast<int>(processor_.overlap());
    if (ImGui::SliderInt("Overlap", &overlap, 0, winSize - 1)) {
        processor_.setOverlap(static_cast<size_t>(overlap));
    }

    const std::vector<float>& raw = processor_.raw();
    const std::vector<float>& rms = processor_.processed();

    if (ImPlot::BeginPlot("EMG")) {
        if (!raw.empty()) {
            ImPlot::PlotLine("Raw", raw.data(), raw.size());
        }
        if (!rms.empty()) {
            ImPlot::PlotLine("RMS", rms.data(), rms.size());
        }
        ImPlot::EndPlot();
    }

    ImGui::End();
}
