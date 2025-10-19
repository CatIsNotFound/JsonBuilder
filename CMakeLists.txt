cmake_minimum_required(VERSION 3.15)
project(JsonBuilder VERSION 1.0.0 LANGUAGES CXX)

# 确保项目版本已设置
if(NOT DEFINED PROJECT_VERSION)
    set(PROJECT_VERSION "1.0.0")
endif()

if(NOT DEFINED PROJECT_VERSION_MAJOR)
    string(REGEX REPLACE "([0-9]+)\.[0-9]+\.[0-9]+" "\\1" PROJECT_VERSION_MAJOR "${PROJECT_VERSION}")
endif()

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 默认设置包含当前项目目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 选项：构建类型使用 Debug 还是 Release 以构建项目（默认为 Release）
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

# 选项：库类型选择
option(BUILD_SHARED_LIBS "Build shared libraries instead of static libraries" OFF)

# 安装路径设置
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}" CACHE PATH "Installation prefix" FORCE)
endif()

# 确保源文件存在
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/Json.cpp" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/Json.h")
    message(FATAL_ERROR "Source files not found! Please ensure src/Json.cpp and src/Json.h exist.")
endif()

# 定义库目标
if(BUILD_SHARED_LIBS)
    add_library(JsonBuilder SHARED
            src/Json.cpp
            src/Json.h
    )
    message(STATUS "Building shared library")
else()
    add_library(JsonBuilder STATIC
            src/Json.cpp
            src/Json.h
    )
    message(STATUS "Building static library")
endif()

# 设置库的属性
set_target_properties(JsonBuilder PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    EXPORT_NAME JsonBuilder
)

# 添加编译选项优化
if(MSVC)
    target_compile_options(JsonBuilder PRIVATE /W4)
else()
    target_compile_options(JsonBuilder PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(JsonBuilder PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# 安装库目标
install(TARGETS JsonBuilder
    EXPORT JsonBuilderTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY src/
    DESTINATION include/JsonBuilder
    FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY docs/
    DESTINATION docs
)

# 安装许可证文件
install(FILES LICENSE
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install(EXPORT JsonBuilderTargets
        FILE JsonBuilderTargets.cmake
        NAMESPACE JsonBuilder::
        DESTINATION lib/cmake/JsonBuilder
)

# 生成版本配置文件
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/JsonBuilderConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
)

# 确保配置文件模板存在
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/JsonBuilderConfig.cmake.in")
    message(WARNING "Config file template not found. Creating a basic template...")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/JsonBuilderConfig.cmake.in"
        "@PACKAGE_INIT@\n\n"
        "include(\"${CMAKE_CURRENT_LIST_DIR}/JsonBuilderTargets.cmake\")\n\n"
        "check_required_components(JsonBuilder)\n"
    )
endif()
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/JsonBuilderConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/JsonBuilderConfig.cmake"
        INSTALL_DESTINATION lib/cmake/JsonBuilder
)
# 安装CMake配置文件
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/JsonBuilderConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/JsonBuilderConfigVersion.cmake"
        DESTINATION lib/cmake/JsonBuilder
)

# 选项：是否构建示例
option(BUILD_EXAMPLES "Build example applications" ON)

# 选项：是否构建测试
option(BUILD_TESTS "Build test suite" ON)

# 示例构建支持
if(BUILD_EXAMPLES)
    message(STATUS "Looking for examples directory...")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples")
        add_subdirectory(examples)
    else()
        message(WARNING "examples directory not found. Creating placeholder...")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    endif()
endif()

# 测试构建支持
if(BUILD_TESTS)
    message(STATUS "Looking for tests directory...")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tests")
        enable_testing()
        add_subdirectory(tests)
    else()
        message(WARNING "tests directory not found. Creating placeholder...")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    endif()
endif()

# 输出配置摘要
message(STATUS "========================= JsonBuilder Configuration =========================")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
if(BUILD_SHARED_LIBS)
    message(STATUS "Library Type: Shared")
else()
    message(STATUS "Library Type: Static")
endif()
message(STATUS "Build Examples: ${BUILD_EXAMPLES}")
message(STATUS "Build Tests: ${BUILD_TESTS}")
message(STATUS "=============================================================================")

# 为IDE生成分组
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES src/Json.cpp src/Json.h)