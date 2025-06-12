# EMG Device Real-Time Analysis & Recording

This project implements real-time visualization, processing, and recording of electromyography (EMG) data over a serial connection. The software is built in C++ and uses Dear ImGui with ImPlot for the graphical user interface.

## Features

- **Serial Data Acquisition**: Connect to a COM port and stream EMG data with adjustable serial settings.
- **Real-Time Processing**: A configurable sliding window feeds the `DataProcessor` class which computes moving averages and RMS values.
- **Interactive Visualization**: Plot raw waveforms and processed features alongside draggable markers representing the processing window.
- **GUI Controls**: Adjust the window size from sliders or by dragging the markers; overlap updates automatically.
- **Data Logging**: Click the GUI button labeled `● 記録` to start saving incoming and processed data to a time-stamped CSV file; the label changes to `■ 停止` while recording.
- **Extensible Architecture**: Modular class design for communication, processing, GUI, and file I/O, allowing new algorithms to be added easily.

## Building

The project uses CMake. After cloning the repository, create a build directory and run:

```bash
cmake -S . -B build
cmake --build build
```

### Running Tests

Unit tests build alongside the main executable. After configuring the project,
run:

```bash
ctest --test-dir build
```

## Requirements

- C++17 compiler
- [Dear ImGui](https://github.com/ocornut/imgui) and [ImPlot](https://github.com/epezent/implot)

## License

This project is released under the MIT License.
