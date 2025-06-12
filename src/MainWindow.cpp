#include "MainWindow.hpp"
#include "SerialCommunicator.hpp"
#include "DataProcessor.hpp"
#include "CSVLogger.hpp"

MainWindow::MainWindow(SerialCommunicator& serial,
                       DataProcessor& processor,
                       CSVLogger& logger)
    : serial_(serial), processor_(processor), logger_(logger) {}

void MainWindow::render() {
    // GUI rendering code using Dear ImGui will go here
}
