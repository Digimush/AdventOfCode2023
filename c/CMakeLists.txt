cmake_minimum_required(VERSION 3.26)
project(c C)

set(CMAKE_C_STANDARD 23)

file(COPY ./day1/input DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/day1")

add_executable(c main.c
        day1/day1Solver.h
        day1/day1Solver.c)
