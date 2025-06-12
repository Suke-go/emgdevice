#pragma once
#include <fstream>
#include <string>

class CSVLogger {
public:
    CSVLogger();
    ~CSVLogger();

    bool open(const std::string& filename);
    void close();
    bool isOpen() const;
    void writeRow(float timestamp, float rawValue, float processedValue);

private:
    std::ofstream file_;
};
