#include "Application.hpp"
#include <memory>
#include "SerialCommunicator.hpp"
#include "DataProcessor.hpp"
#include "CSVLogger.hpp"
#include "MainWindow.hpp"

Application::Application()
    : serial_(std::make_unique<SerialCommunicator>()),
      processor_(std::make_unique<DataProcessor>()),
      logger_(std::make_unique<CSVLogger>()),
      window_(std::make_unique<MainWindow>(*serial_, *processor_, *logger_)) {}

Application::~Application() = default;

int Application::run() {
    // Placeholder for main loop
    return 0;
}
