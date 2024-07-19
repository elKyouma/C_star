cmake_minimum_required(VERSION 3.13)  # CMake version check
project(C_star)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# Specify the output directory for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
#Find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(C_star ${SOURCES})
target_compile_features(C_star PUBLIC cxx_std_20) # or whatever language standard you are using
#Include directories
target_include_directories(C_star PUBLIC includes)


include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)
target_link_libraries(C_star fmt::fmt)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)


enable_testing()

file(GLOB_RECURSE TESTS_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(C_star_tests ${TESTS_SOURCES})

target_link_libraries(
  C_star_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(C_star_tests)
