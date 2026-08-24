cmake_minimum_required(VERSION 3.14)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    PriorityQueue_test
    tests/PriorityQueue_test.cpp
)

target_include_directories(
    PriorityQueue_test
    PRIVATE include
)

target_link_libraries(
    PriorityQueue_test
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(PriorityQueue_test)