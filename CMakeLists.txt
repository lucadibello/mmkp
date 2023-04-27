cmake_minimum_required(VERSION 3.21)
project(mmkp)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(mmkp
        src/data.cpp
        src/data.h
        src/main.cpp src/utility/EasyInstance.cpp src/utility/EasyInstance.h src/utility/FastMath.cpp src/utility/FastMath.h src/greedy/Greedy.cpp src/greedy/Greedy.h src/localSearch/LocalSearch.cpp src/localSearch/LocalSearch.h)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mmkp PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
add_executable(converter
        src/data.cpp
        src/data.h
        src/converter/DataConverter.cpp src/localSearch/LocalSearch.h src/localSearch/LocalSearch.cpp)

add_executable(verifier
        verifier/main.cpp verifier/data.cpp verifier/data.h)