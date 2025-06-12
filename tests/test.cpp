#include "DataProcessor.hpp"
#include "CSVLogger.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <vector>

int main() {
    // DataProcessor RMS computation
    DataProcessor dp;
    dp.setWindowSize(4);
    dp.setOverlap(2);
    std::vector<float> samples{1,2,3,4,5,6};
    dp.processSamples(samples);
    const auto& proc = dp.processed();
    assert(proc.size() == 2);
    float expected1 = std::sqrt((1*1 + 2*2 + 3*3 + 4*4)/4.0f);
    float expected2 = std::sqrt((3*3 + 4*4 + 5*5 + 6*6)/4.0f);
    assert(std::abs(proc[0] - expected1) < 1e-5f);
    assert(std::abs(proc[1] - expected2) < 1e-5f);

    // CSVLogger writes header and rows
    CSVLogger logger;
    assert(logger.open("test_log.csv"));
    logger.writeRow(0.1f, 0.2f, 0.3f);
    logger.close();

    std::ifstream f("test_log.csv");
    std::string line;
    std::getline(f, line);
    assert(line == "Timestamp,RawEMG,RMS");
    std::getline(f, line);
    assert(line == "0.1,0.2,0.3");
    f.close();

    return 0;
}
