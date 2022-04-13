cmake_minimum_required(VERSION 3.10)

project(tests-mill-emulation)

set(PROJECT_HEADER
    board.h
    position.h
    tests_board.h)

set(PROJECT_SOURCE
    board.cpp
    position.cpp
    tests_board.cpp
    tests_main.cpp)

add_executable(tests-mill-emulation ${PROJECT_SOURCE})
