cmake_minimum_required(VERSION 3.10)

project(mill-emulation)

set(PROJECT_HEADER
    board.h
    position.h)

set(PROJECT_SOURCE
    main.cpp
    board.cpp
    position.cpp)

add_executable(mill-emulation ${PROJECT_SOURCE})
