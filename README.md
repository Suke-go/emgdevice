# EMG Device Real-Time Analysis & Recording

This project implements real-time visualization, processing, and recording of electromyography (EMG) data over a serial connection. The software is built in C++ and uses Dear ImGui with ImPlot for the graphical user interface.

## Features

- **Serial Data Acquisition**: Connect to a COM port and stream EMG data with adjustable serial settings.
- **Real-Time Processing**: A configurable sliding window feeds the `DataProcessor` class which computes moving averages and RMS values.
- **Interactive Visualization**: Plot raw waveforms and processed features alongside draggable markers representing the processing window.
- **GUI Controls**: Adjust the window size from sliders or by dragging the markers; overlap updates automatically.
- **Data Logging**: Click the GUI button labeled `● Record` to start saving incoming and processed data to a time-stamped CSV file; the label changes to `■ Stop` while recording.
- **Extensible Architecture**: Modular class design for communication, processing, GUI, and file I/O, allowing new algorithms to be added easily.

## Building

The project uses CMake. After cloning the repository, create a build directory and run:

```bash
cmake -S . -B build
cmake --build build
```

### Building the GUI

If ImGui and ImPlot are present (see [Installing dependencies](#installing-dependencies)),
the main executable will include the graphical interface automatically when
built with the commands above.


### Building with Visual Studio

On Windows you can generate a Visual Studio solution using the provided
`CMakePresets.json` file:

```bash
cmake --preset vs2022
cmake --build --preset vs2022
```

This produces `emgdevice.sln` in the `build` directory which can be opened
directly in Visual Studio for further development or debugging.

### Running Tests

Unit tests build alongside the main executable. After configuring the project,
run:

```bash
ctest --test-dir build
```

## Requirements

- C++17 compiler
- [Dear ImGui](https://github.com/ocornut/imgui) and [ImPlot](https://github.com/epezent/implot)

### Installing dependencies

Download the ImGui and ImPlot source trees and place them under the project's
`include` directory so the headers are available during compilation:
Cloning the repositories copies all required `*.h` and `*.cpp` files (e.g.
`imgui.cpp`, `imgui_draw.cpp`, `implot.cpp`, `implot_items.cpp`) along with the
`imstb_*` headers used by ImGui. Alternatively copy these files manually if you
already maintain local versions of the libraries.

```bash
git clone https://github.com/ocornut/imgui include/imgui
git clone https://github.com/epezent/implot include/implot
```

### Custom library locations

If you already have ImGui or ImPlot installed elsewhere, pass their paths when
running `cmake`:

```bash
cmake -S . -B build -DIMGUI_DIR=/path/to/imgui -DIMPLOT_DIR=/path/to/implot
cmake --build build
```

The variables are optional—if omitted the build falls back to the copies placed
under `include/`.

With the libraries in place you can run the CMake commands shown above to build
the GUI application. If the headers are missing the project will still compile
using stub implementations, but no user interface will be shown.

## License

This project is released under the MIT License.
