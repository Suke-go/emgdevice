#include "SerialCommunicator.hpp"
#include <chrono>
#include <random>

SerialCommunicator::SerialCommunicator(const std::string& portName, int baudRate) {
    open(portName, baudRate);
}

SerialCommunicator::~SerialCommunicator() {
    close();
}

bool SerialCommunicator::isOpen() const {
    return running_;
}

size_t SerialCommunicator::readData(std::vector<float>& out) {
    std::lock_guard<std::mutex> lock(mutex_);
    size_t count = buffer_.size();
    out.insert(out.end(), buffer_.begin(), buffer_.end());
    buffer_.clear();
    return count;
}

void SerialCommunicator::open(const std::string& /*portName*/, int /*baudRate*/) {
    running_ = true;
    worker_ = std::thread(&SerialCommunicator::receiveLoop, this);
}

void SerialCommunicator::close() {
    if (running_) {
        running_ = false;
        if (worker_.joinable()) {
            worker_.join();
        }
    }
}

void SerialCommunicator::receiveLoop() {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    while (running_) {
        float sample = dist(rng);
        {
            std::lock_guard<std::mutex> lock(mutex_);
            buffer_.push_back(sample);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
