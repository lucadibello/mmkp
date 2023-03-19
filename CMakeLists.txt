cmake_minimum_required(VERSION 3.21)
project(mmkp)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(mmkp
        src/data.cpp
        src/data.h
        src/main.cpp src/utility/EasyInstance.cpp src/utility/EasyInstance.h )

add_executable(converter
        src/data.cpp
        src/data.h
        src/converter/DataConverter.cpp)
