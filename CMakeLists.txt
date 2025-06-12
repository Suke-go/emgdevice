cmake_minimum_required(VERSION 3.10)
project(emgdevice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional paths to ImGui and ImPlot headers. If left empty the build will
# fall back to the copies placed under the `include` directory.
set(IMGUI_DIR "" CACHE PATH "Path to ImGui headers")
set(IMPLOT_DIR "" CACHE PATH "Path to ImPlot headers")

file(GLOB SOURCES "src/*.cpp")

add_executable(emgdevice ${SOURCES})

target_include_directories(emgdevice PUBLIC include)
if(IMGUI_DIR)
    target_include_directories(emgdevice PUBLIC ${IMGUI_DIR})
elseif(EXISTS "${CMAKE_SOURCE_DIR}/include/imgui")
    target_include_directories(emgdevice PUBLIC ${CMAKE_SOURCE_DIR}/include/imgui)
endif()
if(IMPLOT_DIR)
    target_include_directories(emgdevice PUBLIC ${IMPLOT_DIR})
elseif(EXISTS "${CMAKE_SOURCE_DIR}/include/implot")
    target_include_directories(emgdevice PUBLIC ${CMAKE_SOURCE_DIR}/include/implot)
endif()

enable_testing()
add_executable(test_emgdevice
    tests/test.cpp
    src/CSVLogger.cpp
    src/DataProcessor.cpp
)
target_include_directories(test_emgdevice PRIVATE include)
if(IMGUI_DIR)
    target_include_directories(test_emgdevice PRIVATE ${IMGUI_DIR})
elseif(EXISTS "${CMAKE_SOURCE_DIR}/include/imgui")
    target_include_directories(test_emgdevice PRIVATE ${CMAKE_SOURCE_DIR}/include/imgui)
endif()
if(IMPLOT_DIR)
    target_include_directories(test_emgdevice PRIVATE ${IMPLOT_DIR})
elseif(EXISTS "${CMAKE_SOURCE_DIR}/include/implot")
    target_include_directories(test_emgdevice PRIVATE ${CMAKE_SOURCE_DIR}/include/implot)
endif()
add_test(NAME unit COMMAND test_emgdevice)
