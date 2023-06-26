cmake_minimum_required(VERSION 3.25)
project(nerplus)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(nerplus
        Table.cpp
        Table.h main.cpp src/table.h src/table.h src/pbar.cpp main_omp.cpp main_omp.cpp test.cpp src/tablempi.h)
