#include "Application.hpp"
#include <chrono>
#include <memory>
#include <thread>
#include <vector>
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
    for (int i = 0; i < 100; ++i) {
        std::vector<float> samples;
        serial_->readData(samples);
        if (!samples.empty()) {
            processor_->processSamples(samples);
        }
        window_->render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
