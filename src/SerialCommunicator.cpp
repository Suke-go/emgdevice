#include "SerialCommunicator.hpp"

SerialCommunicator::SerialCommunicator() = default;
SerialCommunicator::~SerialCommunicator() = default;

bool SerialCommunicator::open(const std::string& /*portName*/, int /*baudRate*/) {
    return false;
}

void SerialCommunicator::close() {
}

bool SerialCommunicator::isOpen() const {
    return false;
}

size_t SerialCommunicator::readData(std::vector<float>& /*buffer*/) {
    return 0;
}
