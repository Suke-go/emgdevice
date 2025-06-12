#include "CSVLogger.hpp"

CSVLogger::CSVLogger() = default;
CSVLogger::~CSVLogger() = default;

bool CSVLogger::open(const std::string& /*filename*/) {
    return false;
}

void CSVLogger::close() {
}

bool CSVLogger::isOpen() const {
    return false;
}

void CSVLogger::writeRow(float /*timestamp*/, float /*rawValue*/, float /*processedValue*/) {
}
