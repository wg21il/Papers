
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(P2832)

include_directories(
    header
)

add_subdirectory(units)

