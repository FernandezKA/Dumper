cmake_minimum_required(VERSION 3.0.0)

project(Dumper VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./Include)

set(INCLUDE 
    ./Include/Memory.h
    ./Include/Dumper.h)

set(SOURCE
    ./Source/Memory.cpp
    ./Source/Dumper.cpp
    ./Source/main.cpp)

add_executable(Dumper ${SOURCE} ${INCLUDE})