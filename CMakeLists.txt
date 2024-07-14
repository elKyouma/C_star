cmake_minimum_required(VERSION 3.13)  # CMake version check
project(C_star)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# Specify the output directory for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Include directories
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(C_star ${SOURCES})
