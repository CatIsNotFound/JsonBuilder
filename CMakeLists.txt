cmake_minimum_required(VERSION 3.31)
project(JsonBuilder)

set(CMAKE_CXX_STANDARD 20)

add_executable(JsonBuilder main.cpp
        src/Json.cpp
        src/Json.h
)
