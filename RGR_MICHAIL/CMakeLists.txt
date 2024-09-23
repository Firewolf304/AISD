cmake_minimum_required(VERSION 3.28)
project(RGR_MICHAIL)

set(CMAKE_CXX_STANDARD 23)

add_executable(RGR_ME main.cpp
        graph.hpp
        Edge.hpp
        Vertex.hpp)
