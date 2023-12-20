cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(problems_project)
set (CMAKE_CXX_STANDARD 20)

include_directories(include)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -O3 -g -fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable (main src/main.cpp src/solution.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
