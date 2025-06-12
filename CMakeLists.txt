cmake_minimum_required(VERSION 3.10)
project(emgdevice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(emgdevice ${SOURCES})

target_include_directories(emgdevice PUBLIC include)

enable_testing()
add_executable(test_emgdevice
    tests/test.cpp
    src/CSVLogger.cpp
    src/DataProcessor.cpp
)
target_include_directories(test_emgdevice PRIVATE include)
add_test(NAME unit COMMAND test_emgdevice)
