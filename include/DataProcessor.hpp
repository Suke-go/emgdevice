#pragma once
#include <vector>

// Processes incoming EMG samples using a sliding window. The class
// computes simple statistics such as moving average and RMS that other
// components can query.
class DataProcessor {
public:
    DataProcessor();

    void setWindowSize(size_t size);
    void setOverlap(size_t overlap);

    // Add new samples to the internal buffer and update processed values
    void processSamples(const std::vector<float>& samples);

    // Convenience wrapper for single-sample updates
    void processSample(float sample);

    // Returns all processed values calculated so far
    const std::vector<float>& processed() const;

private:
    float computeMovingAverage(const std::vector<float>& window) const;
    float computeRMS(const std::vector<float>& window) const;

    size_t windowSize_{1};
    size_t overlap_{0};
    std::vector<float> buffer_;
    std::vector<float> processed_;
};
