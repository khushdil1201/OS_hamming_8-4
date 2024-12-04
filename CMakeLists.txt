cmake_minimum_required(VERSION 3.28)
project(OS)

set(CMAKE_CXX_STANDARD 26)
add_library(Hamming lib.cpp)
add_executable(OS main.cpp
        lib.h
        lib.cpp)
