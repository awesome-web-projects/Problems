cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(problems_project)
set (CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable (main src/main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
