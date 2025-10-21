# Building JsonBuilder with CMake

JsonBuilder supports building and installation using CMake. The details are as follows:

## Configuring the Project

Create a `build` directory in the project root directory and navigate to it:

```bash
mkdir build
cd build
```

Execute the following configuration command:

```bash
cmake ..
```

After configuration is complete, the following information will be output in the terminal:

```
-- ========================= JsonBuilder Configuration =========================
-- Version: 1.0.0
-- Build Type: Release
-- Install Prefix: C:/Program Files (x86)/JsonBuilder/JsonBuilder
-- C++ Standard: 20
-- Library Type: Static
-- Build Examples: OFF
-- Build Tests: OFF
-- =============================================================================
```

The configuration information corresponds to the following:

- **Version**: The version number of JsonBuilder.
- **Build Type**: Build type, such as Release, Debug, etc.
- **Install Prefix**: Installation prefix, specifying the installation path.
- **C++ Standard**: C++ standard version, version **must be `>= 20`**.
- **Library Type**: Library type, static library or shared library.
- **Build Examples**: Whether to build example programs.
- **Build Tests**: Whether to build test programs.

### Supported Build Options

- `CMAKE_BUILD_TYPE`: Specifies the build type, default is `Release`.
- `CMAKE_INSTALL_PREFIX`: Specifies the installation path,

> About the installation path:
>
> - Default is `/usr/local/JsonBuilder` on MacOS/Linux systems,
> - Default is `C:/Program Files (x86)/JsonBuilder/JsonBuilder` on Windows systems).

JsonBuilder provides the following supported build options:

- `BUILD_SHARED_LIBS`: Whether to build a shared library (default: `OFF`)
- `BUILD_EXAMPLES`: Whether to build example programs (default: `ON`)
- `BUILD_TESTS`: Whether to build test programs (default: `ON`)

The following is an example of configuring and using build options:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/lib/JsonBuilder -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
```

The above configuration will build a static library without example programs and test programs, and specify the installation path of the library.

## Installing the Library

If you have completed the project build, execute the following command to install the library:

```bash
cmake --build . --target install
```

After installation is complete, the library files will be located in the specified installation path.

## Using the Library in Your Project

Assuming you have installed the library, you can use it in your project. Here is a simple example:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyJsonApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify JsonBuilder library path (need to modify according to actual installation path)
set(JSON_BUILDER_DIR "/path/to/JsonBuilder")

# Find JsonBuilder library
find_package(JsonBuilder REQUIRED)

# Include JsonBuilder header files
include_directories(${JSON_BUILDER_DIR}/include)

# Add library file search directory
link_directories(${JSON_BUILDER_DIR}/lib)

# Add executable file
add_executable(MyJsonApp main.cpp)

# Link JsonBuilder library
target_link_libraries(MyJsonApp JsonBuilder)
```

In the example above, we assume that the main file of the project is `main.cpp`. Through the `find_package` command, we can find the installed JsonBuilder library. Then, we use the `target_link_libraries` command to link the JsonBuilder library to the executable file `MyJsonApp`.

Please ensure that the correct library path is included in your project's `CMakeLists.txt` file.

This will tell CMake to find the JsonBuilder library in the specified path.

**Note: For imported shared libraries, you also need to add a custom command in `CMakeLists.txt` to copy the shared library to the project directory.**

```cmake
add_custom_command(TARGET TestJson POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${JSON_BUILDER_DIR}/bin
        ${CMAKE_CURRENT_BINARY_DIR}
)
```

After completing the above steps, you only need to include the following header file in your project:

```cpp
#include <JsonBuilder/Json.h>
```

# Learn More

- [Class Reference](class.md)
- [Usage Guide](usage.md)
- [Examples](example.md)