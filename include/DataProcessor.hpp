#pragma once
#include <vector>

class DataProcessor {
public:
    DataProcessor();

    void setWindowSize(size_t size);
    void setOverlap(size_t overlap);

    float processSample(float sample);

private:
    size_t windowSize_{0};
    size_t overlap_{0};
    std::vector<float> buffer_;
};
