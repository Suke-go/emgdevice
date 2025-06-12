#include "CSVLogger.hpp"

CSVLogger::CSVLogger() = default;
CSVLogger::~CSVLogger() = default;

bool CSVLogger::open(const std::string& filename) {
    file_.open(filename);
    if (file_.is_open()) {
        file_ << "Timestamp,RawEMG,RMS" << '\n';
        return true;
    }
    return false;
}

void CSVLogger::close() {
    if (file_.is_open()) {
        file_.close();
    }
}

bool CSVLogger::isOpen() const {
    return file_.is_open();
}

void CSVLogger::writeRow(float timestamp, float rawValue, float processedValue) {
    if (file_.is_open()) {
        file_ << timestamp << ',' << rawValue << ',' << processedValue << '\n';
    }
}
