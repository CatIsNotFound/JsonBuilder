# JsonBuilder 使用方法

JsonBuilder 是一个 C++ 库，用于构建 JSON 数据。它提供了简单易用的 API，用于创建、解析和操作 JSON 数据。

## 安装

### 直接导入【最简单】

JsonBuilder 可以直接导入到项目中，无需安装。

使用以下 Git 目录克隆 JsonBuilder 仓库：
```bash
git clone https://github.com/CatIsNotFound/JsonBuilder.git  
cd JsonBuilder
```

在项目根目录下复制 `src` 目录下的 `Json.h` 和 `Json.cpp` 文件到你的项目目录中。

### 安装 Release 二进制版本

JsonBuilder 可以从 GitHub 上的 [repository](https://github.com/CatIsNotFound/JsonBuilder/releases/latest) 下载最新的 release 版本。

### 手动编译项目

使用以下 Git 目录克隆 JsonBuilder 仓库：
```bash
git clone https://github.com/CatIsNotFound/JsonBuilder.git  
cd JsonBuilder
```

你可以通过 CMake 配置项目并编译安装，具体方法请参看 [使用 CMake 配置 JsonBuilder](cmake.md)。

## 导入库

在你的 C++ 项目中，包含 `Json.h` 文件即可使用 JsonBuilder 库。

```cpp
#include "path/to/JsonBuilder/Json.h"
```

## 简要示例

下面提供两个示例，展示如何使用 JsonBuilder 库创建和操作 JSON 数据。

```cpp
#include <JsonBuilder/Json.h>  // 包含 JsonBuilder 库的头文件
#include "/path/to/Json.h"     // 通过 Json.h 头文件使用 JsonBuilder 库

using namespace JsonBuilder;

int main() {
    // 创建一个 JSON 数组
    JArray array;
    array << 1 << 2 << 3;

    // 创建一个 JSON 对象
    JObject object;
    object["name"] = "John Doe";
    object["age"] = 30;
    object["array"] = array;

    // 创建一个 JSON 解析器
    JParser parser;
    parser.setRootObject(object);

    // 打印解析器的 JSON 字符串表示
    std::cout << parser.dump(4) << std::endl;

    return 0;
}
```

执行上述示例代码后，将在终端下显示以下 JSON 字符串：
```json
{
    "name": "John Doe",
    "age": 30,
    "array": [
        1,
        2,
        3
    ]
}
```

关于更多的示例，你可以参看 [JsonBuilder 使用示例](example.md)。

若需要了解更多的 JsonBuilder 类相关的参考，请参看 [JsonBuilder 类参考](class.md)。

