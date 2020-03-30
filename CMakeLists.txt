cmake_minimum_required(VERSION 3.15)
project(Project02)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project02 main.cpp RentalForm.hpp TopologicalSort.cpp TopologicalSort.h ClientParser.cpp ClientParser.hpp Graph.cpp Graph.h)