#include "DataProcessor.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

DataProcessor::DataProcessor() = default;

void DataProcessor::setWindowSize(size_t size) {
    windowSize_ = size > 0 ? size : 1;
}

void DataProcessor::setOverlap(size_t overlap) {
    overlap_ = overlap;
}

void DataProcessor::processSamples(const std::vector<float>& samples) {
    buffer_.insert(buffer_.end(), samples.begin(), samples.end());
    rawHistory_.insert(rawHistory_.end(), samples.begin(), samples.end());
    if (rawHistory_.size() > rawHistorySize_) {
        rawHistory_.erase(rawHistory_.begin(), rawHistory_.begin() + (rawHistory_.size() - rawHistorySize_));
    }

    while (buffer_.size() >= windowSize_) {
        std::vector<float> window(buffer_.begin(), buffer_.begin() + windowSize_);
        processed_.push_back(computeRMS(window));

        size_t advance = windowSize_ > overlap_ ? windowSize_ - overlap_ : windowSize_;
        buffer_.erase(buffer_.begin(), buffer_.begin() + advance);
    }
}

void DataProcessor::processSample(float sample) {
    std::vector<float> s{sample};
    processSamples(s);
}

const std::vector<float>& DataProcessor::processed() const {
    return processed_;
}

const std::vector<float>& DataProcessor::raw() const {
    return rawHistory_;
}

float DataProcessor::computeMovingAverage(const std::vector<float>& window) const {
    float sum = std::accumulate(window.begin(), window.end(), 0.0f);
    return sum / static_cast<float>(window.size());
}

float DataProcessor::computeRMS(const std::vector<float>& window) const {
    float sumSq = 0.0f;
    for (float v : window) {
        sumSq += v * v;
    }
    return std::sqrt(sumSq / static_cast<float>(window.size()));
}
