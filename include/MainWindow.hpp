#pragma once

class SerialCommunicator;
class DataProcessor;
class CSVLogger;

class MainWindow {
public:
    MainWindow(SerialCommunicator& serial,
               DataProcessor& processor,
               CSVLogger& logger);
    void render();

private:
    SerialCommunicator& serial_;
    DataProcessor& processor_;
    CSVLogger& logger_;

    bool recording_{false};
    double markerStart_{0.0};
    double markerEnd_{100.0};
};
