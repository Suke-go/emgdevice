#pragma once
#include <memory>

class SerialCommunicator;
class DataProcessor;
class CSVLogger;
class MainWindow;

class Application {
public:
    Application();
    ~Application();
    int run();

private:
    std::unique_ptr<SerialCommunicator> serial_;
    std::unique_ptr<DataProcessor> processor_;
    std::unique_ptr<CSVLogger> logger_;
    std::unique_ptr<MainWindow> window_;
};
