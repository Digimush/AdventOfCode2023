cmake_minimum_required(VERSION 3.26)
project(c C)

set(CMAKE_C_STANDARD 23)

file(COPY ./day1/input DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/day1")
file(COPY ./day2/input DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/day2")
file(COPY ./day3/input DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/day3")

add_executable(c main.c
        day1/day1Solver.h
        day1/day1Solver.c
        day2/day2Solver.c
        day2/day2Solver.h
        day3/day3Solver.c
        day3/day3Solver.h
        utils/ArrayList.c
        utils/ArrayList.h)
