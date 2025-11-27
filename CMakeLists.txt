cmake_minimum_required(VERSION 3.10)
project(arthur_port_scanner)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(arthur
    src/main.cpp
    src/scanner.cpp
    src/port_range.cpp
    src/util.cpp
)