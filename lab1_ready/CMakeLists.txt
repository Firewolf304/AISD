cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab1 main.cpp)

include_directories(lab1 src/myvector.hpp)