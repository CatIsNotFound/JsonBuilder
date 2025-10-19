# Building JsonBuilder with CMake

JsonBuilder supports building and installation using CMake. Here are the details:

## Configuring the Project

Create a `build` directory in the project root and enter it:

```bash
mkdir build
cd build
```

Execute the following configuration command:

```bash
cmake ..
```

After configuration, the following information will be output in the terminal:

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

Regarding the configuration information, they correspond to the following:

- **Version**: The version number of JsonBuilder.
- **Build Type**: Build type, such as Release, Debug, etc.
- **Install Prefix**: Installation prefix, specifying the installation path.
- **C++ Standard**: C++ standard version, **must be >= 20**.
- **Library Type**: Library type, static library or shared library.
- **Build Examples**: Whether to build example programs.
- **Build Tests**: Whether to build test programs.

### Supported Build Options

- `CMAKE_BUILD_TYPE`: Specifies the build type, default is `Release`.
- `CMAKE_INSTALL_PREFIX`: Specifies the installation path,

> Regarding the installation path:
>
> - On MacOS/Linux systems, the default is `/usr/local/JsonBuilder`,
> - On Windows systems, the default is `C:/Program Files (x86)/JsonBuilder/JsonBuilder`).

JsonBuilder provides the following supported build options:

- `BUILD_SHARED_LIBS`: Whether to build shared libraries (default: `OFF`)
- `BUILD_EXAMPLES`: Whether to build example programs (default: `ON`)
- `BUILD_TESTS`: Whether to build test programs (default: `ON`)

Here is an example of configuring and using build options:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/lib/JsonBuilder -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
```

The above configuration will build a static library without including example programs and test programs and specify the installation path of the library.

## Installing the Library

If you have completed the project build, execute the following command to install the library:

```bash
cmake --build . --target install
```

After installation, the library files will be located in the specified installation path.

## Using the Library in a Project

Assuming you have installed the library, you can use it in your project. Here is a simple example:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyJsonApp)

set(CMAKE_CXX_STANDARD 20)

# Find JsonBuilder library
find_package(JsonBuilder 1.0.0 REQUIRED)

# Add executable
add_executable(MyJsonApp main.cpp)

# Link JsonBuilder library
target_link_libraries(MyJsonApp JsonBuilder)
```

In the example above, we assume that the main file of the project is `main.cpp`. Through the `find_package` command, we can find the installed JsonBuilder library. Then, we use the `target_link_libraries` command to link the JsonBuilder library to the executable file `MyJsonApp`.

Please ensure that the correct library path is included in the CMakeLists.txt file of your project. For example, on Windows systems, you can add the following statement:

```cmake
set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/JsonBuilder/JsonBuilder")
```

This will tell CMake to look for the JsonBuilder library in the specified path.

After completing the above steps, you can use the JsonBuilder library in your project.

# Learn More

- [Class Reference](class.md)
- [Usage](usage.md)
- [Examples](example.md)