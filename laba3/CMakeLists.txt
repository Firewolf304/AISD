cmake_minimum_required(VERSION 3.28)
project(laba3)

set(CMAKE_CXX_STANDARD 23)
find_package(fmt)
add_executable(laba3 main.cpp
        AST_tree.hpp)
target_link_libraries(laba3 fmt)