cmake_minimum_required(VERSION 3.10)
project(JsonBuilderExample VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../src)

add_executable(JsonBuilderExample
        main.cpp
        examples/AppConfig.h

)

target_link_libraries(JsonBuilderExample PRIVATE JsonBuilder)

