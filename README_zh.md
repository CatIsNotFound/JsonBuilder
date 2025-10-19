# JsonBuilder

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg) ![License](https://img.shields.io/badge/License-MIT-green.svg)

一个轻量级高效的C++ JSON解析和操作库。

## 特性

- 完整的JSON数据类型支持：null、布尔值、整数、浮点数、字符串、数组和对象
- 简单易用的API，用于创建、解析和操作JSON数据
- 支持从文件加载和保存JSON数据
- 自定义异常处理，实现健壮的错误管理
- 支持嵌套结构和复杂JSON操作
- 高效的解析和序列化性能

## 安装

**⚠️ 注意**：本库设计用于 **C++20** 及以上版本。

1. 将 `src` 目录复制到您的项目中。

2. 将源文件包含到您的项目中：
    ```cpp
    #include "src/Json.h"
    ```

## 基本用法

### 从文件解析JSON

```cpp
Json::JParser parser;
parser.parseFromJsonFile("simple.json");
```

### 访问JSON数据

```cpp
// 访问数组元素
const auto& array = parser.array();
std::string name = array.toString(0);

// 访问对象属性
const auto& object = parser.object();
bool flag = object.toBool("active");
int value = object.toInt("id");
std::string text = object.toString("description");
```

### 创建JSON数据

```cpp
// 创建JSON对象
Json::JObject person;
person.set("name", "张三");
person.set("age", 30);
person.set("isEmployed", true);

// 创建JSON数组
Json::JArray hobbies;
hobbies.pushBack("阅读");
hobbies.pushBack("游戏");
hobbies.pushBack("编程");

// 将数组添加到对象
person.set("hobbies", hobbies);

// 使用对象创建解析器
Json::JParser parser(person);
```

### 序列化JSON

```cpp
// 转换为字符串
std::string jsonString = parser.dump(2);  // 使用2个空格缩进

// 保存到文件
parser.dumpToJsonFile("output.json", 2);
```

## 数据类型

该库支持以下JSON数据类型：

- `null` - 由`std::monostate`表示
- `boolean` - `true`或`false`
- `integer` - 32位整数
- `bigint` - 64位整数
- `float` - 32位浮点数
- `double` - 64位浮点数
- `string` - UTF-8编码字符串
- `array` - 值的有序集合
- `object` - 键值对的无序集合

## 错误处理

该库使用异常进行错误处理：

- `KeyIsNotFoundException` - 尝试访问对象中不存在的键时抛出
- `GetBadValueException` - 尝试将值转换为不兼容类型时抛出
- `ParseJsonError` - 解析JSON文本时出错时抛出

```cpp
try {
    std::string value = object.toString("nonExistentKey");
} catch (const Json::KeyIsNotFoundException& e) {
    std::cerr << "错误: " << e.what() << std::endl;
}
```

## 贡献

欢迎贡献！请随时提交问题和拉取请求。

## 许可证

本项目采用 [MIT 许可证](LICENSE)。
