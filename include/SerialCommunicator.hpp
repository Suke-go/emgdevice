#pragma once
#include <string>
#include <vector>

class SerialCommunicator {
public:
    SerialCommunicator();
    ~SerialCommunicator();

    bool open(const std::string& portName, int baudRate);
    void close();
    bool isOpen() const;

    // Reads data into buffer and returns number of samples read
    size_t readData(std::vector<float>& buffer);

private:
    // platform-specific handle placeholder
    void* handle_{};
};
