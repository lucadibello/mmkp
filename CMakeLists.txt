cmake_minimum_required(VERSION 3.21)
project(mmkp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mmkp
        data.cpp
        data.h
        main.cpp)
