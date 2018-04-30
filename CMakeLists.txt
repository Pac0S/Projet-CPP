cmake_minimum_required(VERSION 3.1.3)

project(LS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

add_executable(main main.cpp cellule.cpp grid.cpp)
