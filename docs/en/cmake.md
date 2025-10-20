# Building JsonBuilder with CMake

JsonBuilder supports building and installation using CMake. Here are the details:

## Configuring the Project

Create a `build` directory in the project root and navigate into it:

```bash
mkdir build
cd build
```

Execute the following configuration command:

```bash
cmake ..
```

After configuration completes, the following information will be displayed in the terminal:

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

The configuration information corresponds to:

- **Version**: JsonBuilder's version number.
- **Build Type**: Build type, such as Release, Debug, etc.
- **Install Prefix**: Installation prefix, specifies the installation path.
- **C++ Standard**: C++ standard version, must be `>= 20`.
- **Library Type**: Library type, static or shared.
- **Build Examples**: Whether to build example programs.
- **Build Tests**: Whether to build test programs.

### Supported Build Options

- `CMAKE_BUILD_TYPE`: Specifies the build type, default is `Release`.
- `CMAKE_INSTALL_PREFIX`: Specifies the installation path,

> Regarding installation path:
> 
> - On MacOS/Linux systems, the default is `/usr/local/JsonBuilder`,
> - On Windows systems, the default is `C:/Program Files (x86)/JsonBuilder/JsonBuilder`).

JsonBuilder provides the following supported build options:

- `BUILD_SHARED_LIBS`: Whether to build shared libraries (default: `OFF`)
- `BUILD_EXAMPLES`: Whether to build example programs (default: `ON`)
- `BUILD_TESTS`: Whether to build test programs (default: `ON`)

Here's an example of configuring with build options:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/lib/JsonBuilder -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
```

This configuration will build a static library without example programs and test programs, and specify the library installation path.

## Installing the Library

Once the project has been built, execute the following command to install the library:

```bash
cmake --build . --target install
```

After installation, the library files will be located in the specified installation path.

## Using the Library in Your Project

Assuming you have installed the library, you can use it in your project. Here's a simple example:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyJsonApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify JsonBuilder library path (modify according to actual installation path)
set(JSON_BUILDER_DIR "/path/to/JsonBuilder")

# Find JsonBuilder library
find_package(JsonBuilder REQUIRED)

# Include JsonBuilder header files
include_directories(${JSON_BUILDER_DIR}/include)

# Add library file search directory
link_directories(${JSON_BUILDER_DIR}/lib)

# Add executable
add_executable(MyJsonApp main.cpp)

# Link JsonBuilder library
target_link_libraries(MyJsonApp JsonBuilder)
```

In the example above, we assume the main file of the project is `main.cpp`. Using the `find_package` command, we can find the installed JsonBuilder library. Then, we use the `target_link_libraries` command to link the JsonBuilder library to the executable file `MyJsonApp`.

Please ensure that the correct library path is included in your project's `CMakeLists.txt` file.

This will tell CMake to look for the JsonBuilder library in the specified path.

**Note: For imported shared libraries, you also need to add a custom command in `CMakeLists.txt` to copy the shared library to the project directory.**

```cmake
add_custom_command(TARGET TestJson POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${JSON_BUILDER_DIR}/bin
        ${CMAKE_CURRENT_BINARY_DIR}
)
```

After completing the above steps, in your project, you only need to include the following header file:

```cpp
#include <JsonBuilder/Json.h>
```

# Learn More

- [Class Reference](class.md)
- [Usage](usage.md)
- [Examples](example.md)