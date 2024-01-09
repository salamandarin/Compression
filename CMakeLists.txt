cmake_minimum_required(VERSION 3.12)
project(compression)
add_compile_options(-std=c++17)
add_executable(compression
    compression.cpp
    node.cpp
    compare.cpp
    )
