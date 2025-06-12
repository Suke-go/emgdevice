#include "Application.hpp"
#include <chrono>
#include <memory>
#include <thread>
#include <vector>
#include <ctime>
#include "CSVLogger.hpp"
#include "DataProcessor.hpp"
#include "MainWindow.hpp"
#include "SerialCommunicator.hpp"

Application::Application()
    : serial_(std::make_unique<SerialCommunicator>("COM1", 115200)),
      processor_(std::make_unique<DataProcessor>()),
      logger_(std::make_unique<CSVLogger>()),
      window_(std::make_unique<MainWindow>(*serial_, *processor_, *logger_)) {}

Application::~Application() = default;

int Application::run() {
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::vector<float> samples;
        serial_->readData(samples);
        for (float s : samples) {
            processor_->processSample(s);

            if (logger_->isOpen()) {
                float rms = 0.0f;
                const auto& processed = processor_->processed();
                if (!processed.empty())
                    rms = processed.back();
                auto now = std::chrono::steady_clock::now();
                float ts = std::chrono::duration<float>(now - start).count();
                logger_->writeRow(ts, s, rms);
            }
        }
        window_->render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
