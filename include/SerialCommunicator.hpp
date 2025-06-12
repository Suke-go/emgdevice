#pragma once
#include <string>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>

class SerialCommunicator {
public:
    SerialCommunicator(const std::string& portName, int baudRate);
    ~SerialCommunicator();

    bool isOpen() const;

    // Reads buffered data into `buffer` and returns number of samples copied
    size_t readData(std::vector<float>& buffer);

private:
    void open(const std::string& portName, int baudRate);
    void close();
    void receiveLoop();

    // platform-specific handle placeholder
    void* handle_{};
    std::thread worker_;
    bool running_{false};
    std::deque<float> buffer_;
    std::mutex mutex_;
};
