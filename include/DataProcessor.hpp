#pragma once
#include <vector>

// Processes incoming EMG samples using a sliding window. The class
// computes simple statistics such as moving average and RMS that other
// components can query.
class DataProcessor {
public:
    DataProcessor();

    // Set size of sliding window in number of samples
    void setWindowSize(size_t size);

    // Set overlap between consecutive windows
    void setOverlap(size_t overlap);

    size_t windowSize() const { return windowSize_; }
    size_t overlap() const { return overlap_; }

    // Add new samples to the internal buffer and update processed values
    void processSamples(const std::vector<float>& samples);

    // Convenience wrapper for single-sample updates
    void processSample(float sample);

    // Most recently processed RMS values
    const std::vector<float>& processed() const;

    // Latest raw samples stored for plotting
    const std::vector<float>& raw() const;

private:
    float computeMovingAverage(const std::vector<float>& window) const;
    float computeRMS(const std::vector<float>& window) const;

    size_t windowSize_{1};
    size_t overlap_{0};
    std::vector<float> buffer_;
    std::vector<float> processed_;
    std::vector<float> rawHistory_;
    size_t rawHistorySize_{1000};
};
