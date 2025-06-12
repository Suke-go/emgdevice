cmake_minimum_required(VERSION 3.10)
project(emgdevice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional paths to ImGui and ImPlot sources. If left empty the build will fall
# back to the copies placed under the `include` directory.
set(IMGUI_DIR "" CACHE PATH "Path to ImGui sources")
set(IMPLOT_DIR "" CACHE PATH "Path to ImPlot sources")

file(GLOB SOURCES "src/*.cpp")

add_executable(emgdevice ${SOURCES})

target_include_directories(emgdevice PUBLIC include)

set(IMGUI_PATH "")
if(IMGUI_DIR)
    set(IMGUI_PATH ${IMGUI_DIR})
elseif(EXISTS "${CMAKE_SOURCE_DIR}/include/imgui")
    set(IMGUI_PATH "${CMAKE_SOURCE_DIR}/include/imgui")
endif()

if(IMGUI_PATH)
    target_include_directories(emgdevice PUBLIC ${IMGUI_PATH})
    file(GLOB IMGUI_SRC "${IMGUI_PATH}/*.cpp")
    add_library(imgui STATIC ${IMGUI_SRC})
    target_link_libraries(emgdevice PRIVATE imgui)
endif()

set(IMPLOT_PATH "")
if(IMPLOT_DIR)
    set(IMPLOT_PATH ${IMPLOT_DIR})
elseif(EXISTS "${CMAKE_SOURCE_DIR}/include/implot")
    set(IMPLOT_PATH "${CMAKE_SOURCE_DIR}/include/implot")
endif()

if(IMPLOT_PATH)
    target_include_directories(emgdevice PUBLIC ${IMPLOT_PATH})
    file(GLOB IMPLOT_SRC "${IMPLOT_PATH}/*.cpp")
    add_library(implot STATIC ${IMPLOT_SRC})
    target_link_libraries(emgdevice PRIVATE implot)
endif()

enable_testing()
add_executable(test_emgdevice
    tests/test.cpp
    src/CSVLogger.cpp
    src/DataProcessor.cpp
)
target_include_directories(test_emgdevice PRIVATE include)
if(IMGUI_PATH)
    target_include_directories(test_emgdevice PRIVATE ${IMGUI_PATH})
    target_link_libraries(test_emgdevice PRIVATE imgui)
endif()
if(IMPLOT_PATH)
    target_include_directories(test_emgdevice PRIVATE ${IMPLOT_PATH})
    target_link_libraries(test_emgdevice PRIVATE implot)
endif()
add_test(NAME unit COMMAND test_emgdevice)
