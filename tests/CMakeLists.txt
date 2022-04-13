cmake_minimum_required(VERSION 3.10)

project(tests-mill-emulation)

set(PROJECT_HEADER
    ../src/board.h
    ../src/position.h
    tests_board.h)

set(PROJECT_SOURCE
    ../src/board.cpp
    ../src/position.cpp
    tests_board.cpp
    tests_main.cpp)

add_executable(tests-mill-emulation ${PROJECT_SOURCE})
