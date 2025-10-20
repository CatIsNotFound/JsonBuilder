# JsonBuilder 使用示例

## 示例 1：个人信息

以下示例创建了一个包含个人信息的 JSON 对象：

```cpp
#include <JsonBuilder/Json.h> // 假定使用的是静态/动态库

int main() {
    // 创建一个用于存储个人信息的 JSON 对象
    Json::JObject person;
    // 添加个人信息
    person.set("name", "Alice");
    person.set("age", 18);
    person.set("gender", "female");
    
    // 创建一个包含爱好的数组
    Json::JArray hobbies;
    hobbies.append("reading");
    hobbies.append("traveling");

    // 将爱好数组添加到对象中
    person.set("hobbies", hobbies);

    // 将 Json 对象转换为字符串
    Json::JParser parser(person);
    std::cout << parser.dump(4) << std::endl;
    return 0;
}
```

运行该程序，输出结果如下：

```json
{
    "hobbies": [
        "reading",
        "traveling"
    ],
    "gender": "female",
    "age": 18,
    "name": "Alice"
}
```

注意：关于键值对的顺序，JsonBuilder 库默认按照代码中的添加顺序进行排序，**即最后一个添加的键值会排在最前面**。

你可以通过以下代码进行 `生成 → 解析 → 再生成` 的方式，使得添加的键值符合顺序。

```cpp
Json::JParser parser(person);
std::string json = parser.dump(4);
parser.parse(json);
std::cout << parser.dump(4) << std::endl;
```

## 示例 2：读取多个用户信息的列表

假设你需要读取 `users.json` 文件中的所有用户信息，你可以使用 JsonBuilder 库来实现：

假定 `users.json` 文件内容如下：

```json
[
    {
        "name": "Alice",
        "age": 18,
        "gender": "female"
    },
    {
        "name": "Bob",
        "age": 20,
        "gender": "male"
    }
]
```

```cpp
#include <JsonBuilder/Json.h> // 假定使用的是静态/动态库

int main() {
    // 通过 JParser 解析文件，并指定每行最大长度为 127 个字符
    Json::JParser parser("users.json", 127);
    // 获取解析后的 JSON 数组
    Json::JArray users = parser.array();
    // 遍历 JSON 数组，获取每个用户的信息
    for (size_t i = 0; i < users.size(); i++) {
        auto user = users.toObject(i);
        std::cout << "Name: " << user->toString("name") << std::endl;
        std::cout << "Age: " << user->toInt("age") << std::endl;
        std::cout << "Gender: " << user->toString("gender") << std::endl << std::endl;
    }
    return 0;
}
```

运行该程序，输出结果如下：

```
Name: Alice
Age: 18
Gender: female

Name: Bob
Age: 20
Gender: male
```

## 使用 JsonBuilder Example 程序运行示例

关于 JsonBuilder 库中的提供的所有使用示例，你可以通过 `examples` 目录下的 `examples` 目录查看所有头文件的示例。运行时可直接通过 `examples` 目录下的 `JsonBuilderExamples` 可执行文件以测试运行示例。


# 了解更多

- [类参考](class.md)
- [使用方法](usage.md)
- [使用 CMake 构建 JsonBuilder](cmake.md)]
