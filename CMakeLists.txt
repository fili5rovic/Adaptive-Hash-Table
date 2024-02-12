cmake_minimum_required(VERSION 3.27)
project(AdaptiveHashTable)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(AdaptiveHashTable
        src/HashTable.cpp
        src/main.cpp
        src/QuadraticHashing.cpp)
