cmake_minimum_required(VERSION 3.10)
project(JsonBuilderTestCase VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../src)

add_executable(JsonBuilderTestCase
        main.cpp
        tests/JDataType.h
        tests/JObject.h
        tests/JArray.h
        tests/JParser.h
        tests/JPerformanceTest.h
        ../examples/examples/Personal.h
)

target_link_libraries(JsonBuilderTestCase PRIVATE JsonBuilder)

