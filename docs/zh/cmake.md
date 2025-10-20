# 使用 CMake 构建 JsonBuilder

JsonBuilder 支持使用 CMake 进行构建并安装。具体内容如下：

## 配置项目

在项目根目录下创建一个 `build` 目录，并进入该目录：

```bash
mkdir build
cd build
```

执行如下配置命令：

```bash
cmake ..
```

配置完成后，将在终端中输出以下信息：

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

关于配置信息，分别对应如下：

- **Version**：JsonBuilder 的版本号。
- **Build Type**：构建类型，例如 Release、Debug 等。
- **Install Prefix**：安装前缀，指定安装路径。
- **C++ Standard**：C++ 标准版本，版本**必需 `>= 20`**。
- **Library Type**：库类型，静态库或共享库。
- **Build Examples**：是否构建示例程序。
- **Build Tests**：是否构建测试程序。


### 支持的构建选项

- `CMAKE_BUILD_TYPE`：指定构建类型，默认为 `Release`。
- `CMAKE_INSTALL_PREFIX`：指定安装路径，

> 关于安装路径：
> 
> - MacOS/Linux 系统下默认为 `/usr/local/JsonBuilder`，
> - Windows 系统下默认为 `C:/Program Files (x86)/JsonBuilder/JsonBuilder`）。

JsonBuilder 提供了以下支持的构建选项：

- `BUILD_SHARED_LIBS`：是否构建共享库（默认值：`OFF`）
- `BUILD_EXAMPLES`：是否构建示例程序（默认值：`ON`）
- `BUILD_TESTS`：是否构建测试程序（默认值：`ON`）


下面是配置并使用构建选项的示例：

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/lib/JsonBuilder -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
```

如上配置将构建一个静态库，不包含示例程序和测试程序并指定安装库的路径。

## 安装库

若已经完成项目构建，执行如下命令以安装库：

```bash
cmake --build . --target install
```

安装完成后，库文件将位于指定的安装路径下。

## 在项目中使用库

假设你已经安装了库，你可以在项目中使用它。以下是一个简单的示例：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyJsonApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定 JsonBuilder 库路径（需要根据实际安装路径修改）
set(JSON_BUILDER_DIR "/path/to/JsonBuilder")

# 查找 JsonBuilder 库
find_package(JsonBuilder REQUIRED)

# 包含 JsonBuilder 头文件
include_directories(${JSON_BUILDER_DIR}/include)

# 添加库文件搜索目录
link_directories(${JSON_BUILDER_DIR}/lib)

# 添加可执行文件
add_executable(MyJsonApp main.cpp)

# 链接 JsonBuilder 库
target_link_libraries(MyJsonApp JsonBuilder)
```

在上面的示例中，我们假设项目的主文件为 `main.cpp`。通过 `find_package` 命令，我们可以找到安装的 JsonBuilder 库。然后，我们使用 `target_link_libraries` 命令将 JsonBuilder 库链接到可执行文件 `MyJsonApp` 中。

请确保在项目的 `CMakeLists.txt` 文件中包含了正确的库路径。

这将告诉 CMake 在指定路径下查找 JsonBuilder 库。

**注意：对于导入的共享库，你还需要在 `CMakeLists.txt` 中添加自定义命令，将共享库复制到项目目录下。**

```cmake
add_custom_command(TARGET TestJson POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${JSON_BUILDER_DIR}/bin
        ${CMAKE_CURRENT_BINARY_DIR}
)
```

完成以上步骤后，在你的项目中仅需包含以下头文件即可：

```cpp
#include <JsonBuilder/Json.h>
```

# 了解更多

- [类参考](class.md)
- [使用方法](usage.md)
- [使用示例](example.md)
