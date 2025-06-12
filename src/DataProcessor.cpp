#include "DataProcessor.hpp"

DataProcessor::DataProcessor() = default;

void DataProcessor::setWindowSize(size_t size) {
    windowSize_ = size;
}

void DataProcessor::setOverlap(size_t overlap) {
    overlap_ = overlap;
}

float DataProcessor::processSample(float /*sample*/) {
    return 0.0f;
}
