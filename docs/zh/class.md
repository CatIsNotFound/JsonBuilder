# JsonBuilder 类参考

JsonBuilder 库包含以下类：

- JsonBuilder（命名空间）
    - `JObject`：对象类
    - `JArray`：数组类
    - `JValue`：值类
    - `JParser`: JSON 解析器类
    - `JDataType`：数据类型枚举
    - `JException`：异常命名空间
        - `KeyIsNotFoundException`：键未找到异常（通常出现在对象中访问不存在的键时）
        - `GetBadValueException`：获取错误值异常（通常出现在尝试将一个值转换为不兼容的类型时）
        - `ParseJsonError`：解析 JSON 错误（通常出现在 JSON 文本格式错误时）

## JObject 类

JObject 类用于创建和操作 JSON 对象。以下是 JObject 类的成员函数和用法：

### 构造函数

`JObject()`：创建一个空的 JSON 对象。

用法：

```cpp
Json::JObject object;
```

### 设置键值对

#### `set()`

`void set(const std::string& key, const JValue& value)`：设置 JSON 对象的键值对。

示例用法 1：创建一个键为 "name"，值为 "John Doe" 的键值对。

```cpp
object.set("name", Json::JValue("John Doe"));
```

若要创建一个嵌套对象，请使用 `JObject` 构造函数。

示例用法 2：接示例用法 1，再创建一个键为 "address"，值为嵌套对象的键值对。

```cpp
Json::JObject addressObject;
addressObject.set("city", Json::JValue("New York"));
object.set("address", addressObject);
```

#### `operator[]`

`JValue& operator[](const std::string& key)`：通过键访问 JSON 对象中的值。

示例用法 3：使用 `operator[]` 创建 "age" 键并设置其对应的值为 30。

```cpp
object["age"] = Json::JValue(30);
```

当然，你也可以使用 `operator[]` 设置已存在的键并设置其值。这里不过多赘述。


### 获取键值对

#### `get()`

`JValue & get(const std::string& key)`：获取 JSON 对象中指定键的值。

示例用法 4：获取 "name" 键对应的值。

```cpp
Json::JValue nameValue = object.get("name");
```

#### `operator[]`

`JValue& operator[](const std::string& key)`：通过键访问 JSON 对象中的值。

示例用法 5：使用 `operator[]` 获取 "age" 键对应的值。

```cpp
Json::JValue ageValue = object["age"];
int age = std::get<int32_t>(ageValue);
```

#### `toXXX()`

JObject 提供了以下方法将 JSON 对象转换为其他数据类型：

- `bool toBool(const std::string& key) const`: 将 JSON 对象中的键转换为布尔值。
- `int32_t toInt(const std::string& key) const`: 将 JSON 对象中的键转换为 32 位整数。
- `int64_t toBigInt(const std::string& key) const`: 将 JSON 对象中的键转换为 64 位整数。
- `float toFloat(const std::string& key) const`: 将 JSON 对象中的键转换为 32 位浮点数。
- `double toDouble(const std::string& key) const`: 将 JSON 对象中的键转换为 64 位浮点数。
- `std::string toString(const std::string& key) const`: 将 JSON 对象转换为字符串。
- `JArray toArray(const std::string& key) const`: 将 JSON 对象转换为数组。
- `JObject toObject(const std::string& key) const`: 将 JSON 对象转换为对象。

其中，对于存储整数值类型的数据，不管 `JValue` 中存储的是 `int32_t` 还是 `int64_t`，都可以使用 `toInt()` 或 `toBigInt()` 方法将其转换为 `int32_t` 或 `int64_t` 类型。
对于存储浮点数值类型的数据，不管 `JValue` 中存储的是 `float` 还是 `double`，都可以使用 `toFloat()` 或 `toDouble()` 方法将其转换为 `float` 或 `double` 类型。

> 注意：
> 
> - 当使用 `toInt()` 方法将 `int64_t` 类型的值转换为 `int32_t` 类型时，可能会丢失高位数据。
> - 当使用 `toFloat()` 方法将 `double` 类型的值转换为 `float` 类型时，可能会导致精度损失。

示例用法 6：将 "age" 键对应的值转换为 32 位整数。

```cpp
int32_t age = object.toInt("age");
```

### 其它函数

#### `keys()`

`std::vector<std::string> keys() const`：获取 JSON 对象中所有键的列表。

示例用法 7：获取 JSON 对象中所有键的列表。

```cpp
std::vector<std::string> keyList = object.keys();
```

#### `isNull()`

`bool isNull(const std::string& key) const`：检查 JSON 对象中指定键是否为 `null`。

示例用法 8：检查 "name" 键是否为 `null`。

```cpp
bool isNameNull = object.isNull("name");
```

#### `begin()`, `end()`

非 `const` 版本：

- `std::vector<JValue>::iterator begin()`：返回指向 JSON 对象中第一个值的迭代器。
- `std::vector<JValue>::iterator end()`：返回指向 JSON 对象中最后一个值的迭代器。

`const` 版本：

- `std::vector<JValue>::constIterator begin() const`：返回指向 JSON 对象中第一个值的迭代器。
- `std::vector<JValue>::constIterator end() const`：返回指向 JSON 对象中最后一个值的迭代器。

示例用法 9：遍历 JSON 对象中的所有值。

```cpp
for (auto it = object.begin(); it != object.end(); ++it) {
    Json::JValue value = *it;
    // 处理 value
}
```

或者也可以使用基于范围的循环：

```cpp
for (const auto& value : object) {
    // 处理 value
}
```

#### `size()`

`size_t size() const` 方法返回 JSON 对象中包含的键值对数量。

#### `valid()`

`bool valid(const std::string& key) const` 方法检查 JSON 对象中是否存在指定键。

示例用法 10：检查 "age" 键是否存在。

```cpp
bool isAgeValid = object.valid("age");
```

#### `remove()`

`void remove(const std::string& key)` 方法删除 JSON 对象中指定键对应的键值对。

示例用法 11：删除 "age" 键对应的键值对。

```cpp
object.remove("age");
```

#### `clear()`

`void clear()` 方法清空 JSON 对象，删除所有键值对。

示例用法 12：清空 JSON 对象。

```cpp
object.clear();
```

## JArray 类

JArray 类用于创建和操作 JSON 数组。以下是 JArray 类的成员函数和用法：

### 构造函数

- `JArray()`：创建一个空的 JSON 数组。
- `JArray(const std::vector<JValue>&& values)`：创建一个包含指定值的 JSON 数组。


示例用法 1：创建一个空的 JSON 数组。

```cpp
Json::JArray array;
```

示例用法 2：创建一个包含多个值的 JSON 数组。

```cpp
Json::JArray array({1, 2, 3, true, "null"});
```

### 添加元素

JArray 类支持以下几种添加元素的方式：

- `void append(const JValue& value)`：向 JSON 数组的末尾添加一个元素。
- `void pushBack(const JValue& value)`：向 JSON 数组的末尾添加一个元素。(同 `append()` 函数)
- `void pushFront(const JValue& value)`：向 JSON 数组的开头添加一个元素。
- `void insert(size_t index, const JValue& value)`：在指定位置插入一个元素。
- `void insert(size_t index, const JArray& array)`：在指定位置插入一个 JSON 数组。
- `void insert(size_t index, const JObject& object)`：在指定位置插入一个 JSON 对象。

示例用法 2：向 JSON 数组在不同位置上添加多个不同类型的元素

```cpp
Json::JArray array;
array.append(true);
array.pushBack(Json::JObject());
array.pushFront(123);
array.insert(1, "hello");
array.insert(2, Json::JArray());
```

执行后，`array` 数组内的元素分别为：`[123, "hello", [], true, {}]`。

-------

JArray 还提供了基于 `<<` 运算符的添加元素方式：

`JArray & operator<<(const JValue& value)`：使用 `<<` 运算符向 JSON 数组的末尾添加一个元素。
`JArray & operator<<(const JArray& array)`：使用 `<<` 运算符向 JSON 数组的末尾添加一个 JSON 数组。
`JArray & operator<<(const JObject& object)`：使用 `<<` 运算符向 JSON 数组的末尾添加一个 JSON 对象。

示例用法 3：使用 `<<` 运算符向 JSON 数组的末尾添加多个不同类型的元素

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
```

执行后，`array` 数组内的元素分别为：`[true, {}, 123, "hello", []]`。

### 移除元素

`void remove(size_t index)`：从 JSON 数组中移除指定位置的元素。
`void popBack()`：从 JSON 数组的末尾移除一个元素。
`void popFront()`：从 JSON 数组的开头移除一个元素。
`void clear()`：清空 JSON 数组，删除所有元素。

示例用法 4：从 JSON 数组中移除指定位置的元素

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
array.remove(2);
array.popBack();
array.popFront();
```

执行后，`array` 数组内的元素分别为：`[{}, "hello"]`。

### 访问元素

#### `toXXX()`

JArray 类还提供了 `toXXX()` 方法，用于将 JSON 数组中的某一元素转换为不同数据类型的值。

- `bool toBool(size_t index) const`: 将 JSON 数组中指定位置的元素转换为布尔值。
- `int32_t toInt(size_t index) const`: 将 JSON 数组中指定位置的元素转换为 32 位整数。
- `int64_t toBigInt(size_t index) const`: 将 JSON 数组中指定位置的元素转换为 64 位整数。
- `float toFloat(size_t index) const`: 将 JSON 数组中指定位置的元素转换为 32 位浮点数。
- `double toDouble(size_t index) const`: 将 JSON 数组中指定位置的元素转换为 64 位浮点数。
- `const std::string& toString(size_t index) const`: 将 JSON 数组中指定位置的元素转换为字符串。
- `const JArray* toArray(size_t index) const`: 将 JSON 数组中指定位置的元素转换为数组。
- `const JObject* toObject(size_t index) const`: 将 JSON 数组中指定位置的元素转换为对象。

其中，对于存储整数值类型的数据，不管 `JValue` 中存储的是 `int32_t` 还是 `int64_t`，都可以使用 `toInt()` 或 `toBigInt()` 方法将其转换为 `int32_t` 或 `int64_t` 类型。
对于存储浮点数值类型的数据，不管 `JValue` 中存储的是 `float` 还是 `double`，都可以使用 `toFloat()` 或 `toDouble()` 方法将其转换为 `float` 或 `double` 类型。

> 注意：
> 
> - 当使用 `toInt()` 方法将 `int64_t` 类型的值转换为 `int32_t` 类型时，可能会丢失高位数据。
> - 当使用 `toFloat()` 方法将 `double` 类型的值转换为 `float` 类型时，可能会导致精度损失。

示例用法 5：访问数组中的第 3 个元素

```cpp
Json::JArray array;
array << 100 << 200 << 300 << 400 << 500;
int32_t thirdElement = array.toInt(2);
```

执行后，`thirdElement` 变量的值为 `300`。

#### `operator[]`

`JValue operator[](size_t index) const`：返回 JSON 数组中指定位置的元素。

示例用法 6：访问 JSON 数组中指定位置的元素

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
Json::JValue value = array[2];
```

执行后，`value` 变量的值为 `123`。

### 其它函数

#### `size()`, `length()`

- `size_t size() const` ：返回 JSON 数组中包含的元素数量。
- `size_t length() const` ：返回 JSON 数组中包含的元素数量。(同 `size()` 函数)

#### `isNull()`

- `bool isNull(size_t index) const` ：检查 JSON 数组中指定位置的元素是否为 `null`。

#### `begin()`, `end()`

非 `const` 版本：

- `iterator begin()`：返回指向 JSON 数组开头的迭代器。
- `iterator end()`：返回指向 JSON 数组末尾的迭代器。

`const` 版本：

- `constIterator begin() const`：返回指向 JSON 数组开头的迭代器。
- `constIterator end() const`：返回指向 JSON 数组末尾的迭代器。

示例用法 7：遍历 JSON 数组中的所有元素。

```cpp
for (auto it = array.begin(); it != array.end(); ++it) {
    Json::JValue value = *it;
    // 处理 value
}
```

或者可以使用基于范围的 `for` 循环来遍历 JSON 数组中的所有元素：

```cpp
for (const auto& value : array) {
    // 处理 value
}
```

#### `sort()`

- `void sort(const std::function<bool(JValue&, JValue&)>& sort_function)`：对 JSON 数组中的元素进行排序。


> 注意：
> 
> - 排序函数 `sort_function` 必须是一个函数对象，用于比较两个 `JValue` 对象的大小。
> - 排序函数 `sort_function` 必须返回一个 `bool` 类型的值，用于指示两个 `JValue` 对象的相对顺序。

示例用法 8：对 JSON 数组中的元素进行排序

```cpp
Json::JArray array;
array << 3 << 1 << 4 << 2 << 5;
array.sort([](Json::JValue& a, Json::JValue& b) {
    int v1 = std::get<int32_t>(a);
    int v2 = std::get<int32_t>(b);
    return v1 < v2;
});
```

执行后，`array` 数组内的元素分别为：`[1, 2, 3, 4, 5]`。

## JValue

JValue 属于类型别名，其类型原型为：

```cpp
using JValue = std::variant<
                std::monostate, 
                bool, 
                int32_t, 
                int64_t, 
                float, 
                double, 
                std::string, 
                std::shared_ptr<Json::JArray>, 
                std::shared_ptr<Json::JObject>
                >;
```

JValue 本身不提供用于转换数据类型的函数以及设置数据类型的函数，但是可以通过 `std::get()` 函数获取数据类型，并使用 `std::holds_alternative()` 函数判断数据类型。

示例用法 1：判断 `value` 的数据类型是否为 `int32_t` 类型

```cpp
Json::JValue value = 123;
if (std::holds_alternative<int32_t>(value)) {
    int32_t intValue = std::get<int32_t>(value);
    // 处理 intValue
}
```

对于 `JArray` 或 `JObject` 类型的数据，可以通过 `std::get()` 函数获取对应的指针，然后使用指针来访问数据。

示例用法 2：获取 `array` 中的第二个元素

```cpp
Json::JArray array;
Json::JObject sample;
sample["key1"] = "value1";
sample["key2"] = "value2";
sample["key3"] = "value3";

array << true << sample << 123 << "hello" << Json::JArray();
auto secondValue = std::get<std::shared_ptr<Json::JArray>>(array[1]);
for (auto& v : *secondValue) {
    std::cout << v.toString() << std::endl;
}
```

## JGet 类

JGet 类用于获取 JValue 对象中的数据。你可以通过如下方式将 `JValue` 对象转换为对应的数据类型：

- `JGet::toBool()`：将 `JValue` 对象转换为布尔值。
- `JGet::toInt()`：将 `JValue` 对象转换为整数值。
- `JGet::toBigInt()`：将 `JValue` 对象转换为大整数值。
- `JGet::toFloat()`：将 `JValue` 对象转换为浮点数值。
- `JGet::toString()`：将 `JValue` 对象转换为字符串。
- `JGet::toArray()`：将 `JValue` 对象转换为 JSON 数组指针。
- `JGet::toObject()`：将 `JValue` 对象转换为 JSON 对象指针。

不仅如此，JGet 类还提供了判断数据类型的函数，你可以使用这些函数来判断 `JValue` 对象的具体数据类型。

- `JGet::isNull()`：判断 `JValue` 对象是否为 `null`。
- `JGet::isBool()`：判断 `JValue` 对象是否为布尔值。
- `JGet::isInt()`：判断 `JValue` 对象是否为整数值。
- `JGet::isBigInt()`：判断 `JValue` 对象是否为大整数值。
- `JGet::isFloat()`：判断 `JValue` 对象是否为浮点数值。
- `JGet::isDouble()`：判断 `JValue` 对象是否为双精度浮点数值。
- `JGet::isString()`：判断 `JValue` 对象是否为字符串。
- `JGet::isArray()`：判断 `JValue` 对象是否为 JSON 数组。
- `JGet::isObject()`：判断 `JValue` 对象是否为 JSON 对象。

以下是关于 JGet 类的示例用法：

示例用法 1：将 `JValue` 对象转换为字符串

```cpp
Json::JValue value = "hello";
std::string str = Json::JGet::toString(value);
```

执行后，`str` 变量的值为 `"hello"`。

示例用法 2：将 `JValue` 对象转换为 `JArray` 对象并遍历所有元素

```cpp
Json::JArray array({1, 2, 3, true, "null"});
for (auto& v : array) {
    if (Json::JGet::isInt(v))
        std::cout << Json::JGet::toInt(v) << " ";
    else if (Json::JGet::isBool(v))
        std::cout << (Json::JGet::toBool(v) ? "true" : "false") << " ";
    else if (Json::JGet::isString(v))
        std::cout << Json::JGet::toString(v) << " ";
    // p.s: 示例中仅处理三种数据类型，你可以根据需要添加其他判断逻辑
}
```

执行后，输出结果为：

```
null
```


## JParser 类

JParser 类用于生成和解析 JSON 数据。以下是 JParser 类的成员函数和用法：

### 构造函数

- `JParser()`：创建一个空的 JParser 对象。
- `JParser(const std::string& file_name, size_t max_cols_inline = 1024)`：创建一个 JParser 对象，并从指定的 JSON 文件中加载数据。每行最多读取 `max_cols_inline` 个字符（默认行内最多读取 1024 个字符）。
- `JParser(const JObject& root_object)`：创建一个 JParser 对象，并使用指定的 JSON 对象初始化数据。
- `JParser(const JArray& root_array)`：创建一个 JParser 对象，并使用指定的 JSON 数组初始化数据。

示例用法 1：从 `config.json` 文件中加载数据，并设置每行最多读取 127 个字符。

```cpp
Json::JParser parser("config.json", 127);
```

示例用法 2：使用 JSON 对象初始化数据

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
```

### 解析数据

JParser 类提供了以下解析 JSON 数据的方法：

#### `parse()`

`void parse(const std::string& json)`：解析指定的 JSON 字符串。

示例用法 1：从 JSON 字符串中解析数据并获取对象的键列表

```cpp
std::string json = R"(
{
    "key1": "value1",
    "key2": "value2",
    "key3": "value3",
    "array": [1, 2, 3, 4, 5]
}
)";

Json::JParser parser;
parser.parse(json);

auto& object = parser.object();
auto keys_list = object.keys();
size_t keys_size = keys_list.size(), i = 0;
std::cout << "[";
for (auto& key : keys_list) {
    std::cout << key;
    if (i < keys_size - 1) {
        std::cout << ", ";
    }
}
std::cout << "]" << std::endl;
```

执行后，输出结果为：
```
["key1", "key2", "key3", "array"]
```

#### `parseFromJsonFile()`

`bool parseFromJsonFile(const std::string& file_name, size_t max_cols_inline = 1024)`：从指定的 JSON 文件中加载数据并解析。每行最多读取 `max_cols_inline` 个字符（默认行内最多读取 1024 个字符）。

示例用法 2：从 `config.json` 文件中加载数据并解析

```cpp
Json::JParser parser;
bool is_success = parser.parseFromJsonFile("config.json");
if (is_success) {
    // Parsed successfully
} else {
    // Failed to parse JSON file
}
```

### 生成数据

JParser 类提供了以下生成 JSON 数据的方法：

#### `dump()`

`std::string dump(size_t indent = 2)`：将 JSON 数据转换为字符串。

示例用法 1：将 JSON 对象转换为字符串

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
std::string json = parser.dump(4);
std::cout << json << std::endl;
```

执行后，输出结果为：
```json
{
    "key1": "value1",
    "key2": "value2",
    "key3": "value3"
}
```

示例用法 2：将 JSON 数组转换为字符串

```cpp
Json::JArray array;
array << 1 << 2 << 3 << 4 << 5;

Json::JParser parser(array);
std::string json = parser.dump(4);
std::cout << json << std::endl;
```

执行后，输出结果为：
```json
[
    1,
    2,
    3,
    4,
    5
]
```

示例用法 3：添加一些空数组、空对象、空值到 JSON 对象中

```cpp
Json::JObject obj;
obj["null"] = std::monostate{};
obj["null_object"] = Json::JObject();
obj["null_array"] = Json::JArray();

Json::JParser parser(obj);
parser.dump(4);
```

输出的 `config.json` 文件内容如下：

```json
{
    "null": null,
    "null_object": {},
    "null_array": []
}
```


#### `dumpToJsonFile()`

`bool dumpToJsonFile(const std::string& file_name, size_t indent = 2)`：将 JSON 数据转换为字符串并写入指定的 JSON 文件。

示例用法 1：将 JSON 对象转换为字符串并写入 `config.json` 文件

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
parser.dumpToJsonFile("config.json", 4);
```

输出的 `config.json` 文件内容如下：

```json
{
    "key1": "value1",
    "key2": "value2",
    "key3": "value3"
}
```

示例用法 2：将 JSON 数组转换为字符串并写入 `config.json` 文件

```cpp
Json::JArray array;
array << 1 << 2 << 3 << 4 << 5;

Json::JParser parser(array);
parser.dumpToJsonFile("config.json", 4);
```

输出的 `config.json` 文件内容如下：

```json
[
    1,
    2,
    3,
    4,
    5
]
```

示例用法 3：添加一些空数组、空对象、空值到 JSON 对象中

```cpp
Json::JObject obj;
obj["null"] = std::monostate{};
obj["null_object"] = Json::JObject();
obj["null_array"] = Json::JArray();

Json::JParser parser(obj);
parser.dumpToJsonFile("config.json", 4);
```

输出的 `config.json` 文件内容如下：

```json
{
    "null": null,
    "null_object": {},
    "null_array": []
}
```

### 设置根对象或根数组

JParser 类提供了以下方法来设置根对象或根数组：

#### `setRootObject()`

`void setRootObject(JObject& object)`：设置解析器的根对象为指定的 JSON 对象。

#### `setRootArray()`

`void setRootArray(JArray& array)`：设置解析器的根数组为指定的 JSON 数组。

同时，还提供了以下方法来获取当前的根对象或根数组：

#### `object()`

`const JObject& object() const`：返回解析器的当前根对象。

#### `array()`

`const JArray& array() const`：返回解析器的当前根数组。

# 了解更多

- [使用方法](usage.md)
- [使用示例](example.md)
- [使用 CMake 构建 JsonBuilder](cmake.md)

