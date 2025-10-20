# JsonBuilder Class Reference

This document provides detailed reference information for JsonBuilder library classes, including the methods, properties, and usage examples for each class.

## JObject Class

The JObject class is used to create and manipulate JSON objects. Here are its member functions and usage:

### Construction

- `JObject()`: Creates an empty JSON object.
- `JObject(std::initializer_list<std::pair<const std::string, JValue>> init)`: Creates a JSON object with initial values.

Example Usage 1: Creating an empty JSON object.

```cpp
Json::JObject object;
```

Example Usage 2: Creating a JSON object with initial values.

```cpp
Json::JObject object = {
    {"name", "Tom"},
    {"age", 25},
    {"isStudent", true}
};
```

### Setting Values

JObject provides the following methods to set values:

- `void set(const std::string& key, const JValue& value)`: Sets a value for a specified key.
- `void set(const std::string& key, bool value)`: Sets a boolean value for a specified key.
- `void set(const std::string& key, int32_t value)`: Sets a 32-bit integer value for a specified key.
- `void set(const std::string& key, int64_t value)`: Sets a 64-bit integer value for a specified key.
- `void set(const std::string& key, float value)`: Sets a 32-bit floating point value for a specified key.
- `void set(const std::string& key, double value)`: Sets a 64-bit floating point value for a specified key.
- `void set(const std::string& key, const std::string& value)`: Sets a string value for a specified key.
- `void set(const std::string& key, std::string&& value)`: Sets a string value for a specified key (move semantics).
- `void set(const std::string& key, const JObject& value)`: Sets a JSON object for a specified key.
- `void set(const std::string& key, JObject&& value)`: Sets a JSON object for a specified key (move semantics).
- `void set(const std::string& key, const JArray& value)`: Sets a JSON array for a specified key.
- `void set(const std::string& key, JArray&& value)`: Sets a JSON array for a specified key (move semantics).
- `void set(const std::string& key, std::monostate)`: Sets a null value for a specified key.

Example Usage 3: Setting values of different types for different keys

```cpp
Json::JObject object;
object.set("name", "Tom");
object.set("age", 25);
object.set("isStudent", true);
object.set("scores", Json::JArray({85, 90, 95}));
object.set("address", Json::JObject({{"city", "Beijing"}, {"district", "Haidian"}}));
object.set("null_value", std::monostate{});
```

JObject also supports setting values through the `[]` operator:

- `JValue& operator[](const std::string& key)`: Returns a reference to the value associated with the specified key.

Example Usage 4: Setting values using the `[]` operator

```cpp
Json::JObject object;
object["name"] = "Tom";
object["age"] = 25;
object["isStudent"] = true;
object["scores"] = Json::JArray({85, 90, 95});
object["address"] = Json::JObject({{"city", "Beijing"}, {"district", "Haidian"}});
object["null_value"] = std::monostate{};
```

### Getting Values

#### `get()`

- `JValue get(const std::string& key) const`: Gets the value associated with the specified key.

Example Usage 5: Getting a value using the `get()` method

```cpp
Json::JObject object = {"name", "Tom"};
Json::JValue nameValue = object.get("name");
```

#### `toXXX()`

JObject provides `toXXX()` methods for converting values in the JSON object to different data types:

- `bool toBool(const std::string& key) const`: Converts the value associated with the specified key to a boolean value.
- `int32_t toInt(const std::string& key) const`: Converts the value associated with the specified key to a 32-bit integer.
- `int64_t toBigInt(const std::string& key) const`: Converts the value associated with the specified key to a 64-bit integer.
- `float toFloat(const std::string& key) const`: Converts the value associated with the specified key to a 32-bit floating point number.
- `double toDouble(const std::string& key) const`: Converts the value associated with the specified key to a 64-bit floating point number.
- `const std::string& toString(const std::string& key) const`: Converts the value associated with the specified key to a string.
- `const JArray* toArray(const std::string& key) const`: Converts the value associated with the specified key to an array.
- `const JObject* toObject(const std::string& key) const`: Converts the value associated with the specified key to an object.

For integer types, whether the JValue stores an `int32_t` or `int64_t`, you can use `toInt()` or `toBigInt()` to convert it to `int32_t` or `int64_t`. Similarly for floating point types.

> Note:
> 
> - When converting an `int64_t` value to `int32_t` using `toInt()`, higher-order bits may be lost.
> - When converting a `double` value to `float` using `toFloat()`, precision may be lost.

Example Usage 6: Converting values to different data types

```cpp
Json::JObject object = {
    {"name", "Tom"},
    {"age", 25},
    {"isStudent", true},
    {"scores", Json::JArray({85, 90, 95})}
};

std::string name = object.toString("name");    // name = "Tom"
int32_t age = object.toInt("age");             // age = 25
bool isStudent = object.toBool("isStudent");   // isStudent = true
const Json::JArray* scores = object.toArray("scores");
```

#### `operator[]`

- `JValue operator[](const std::string& key) const`: Returns the value associated with the specified key.

Example Usage 7: Getting a value using the `[]` operator

```cpp
Json::JObject object = {"name", "Tom"};
Json::JValue nameValue = object["name"];
```

### Removing Keys

- `void remove(const std::string& key)`: Removes the key-value pair associated with the specified key from the JSON object.

Example Usage 8: Removing a key from the JSON object

```cpp
Json::JObject object = {
    {"name", "Tom"},
    {"age", 25}
};
object.remove("age");
```

### Checking Keys

- `bool has(const std::string& key) const`: Checks if the JSON object contains a specified key.
- `bool isNull(const std::string& key) const`: Checks if the value associated with the specified key is `null`.

Example Usage 9: Checking if a key exists

```cpp
Json::JObject object = {"name", "Tom"};
if (object.has("name")) {
    // Process the key
}
```

### Iterating Over Keys

#### `keys()`

- `const std::vector<std::string>& keys() const`: Returns a list of all keys in the JSON object.

Example Usage 10: Getting a list of all keys

```cpp
Json::JObject object = {
    {"name", "Tom"},
    {"age", 25},
    {"isStudent", true}
};

const auto& keys = object.keys();
for (const auto& key : keys) {
    std::cout << key << std::endl;
}
```

#### `begin()`, `end()`

Non-const version:

- `iterator begin()`: Returns an iterator pointing to the beginning of the JSON object.
- `iterator end()`: Returns an iterator pointing to the end of the JSON object.

Const version:

- `constIterator begin() const`: Returns a const iterator pointing to the beginning of the JSON object.
- `constIterator end() const`: Returns a const iterator pointing to the end of the JSON object.

Example Usage 11: Iterating over all key-value pairs in a JSON object

```cpp
for (auto it = object.begin(); it != object.end(); ++it) {
    const std::string& key = it->first;
    const Json::JValue& value = it->second;
    // Process key and value
}
```

Or you can use a range-based for loop:

```cpp
for (const auto& [key, value] : object) {
    // Process key and value
}
```

### Other Methods

#### `size()`, `length()`

- `size_t size() const`: Returns the number of key-value pairs in the JSON object.
- `size_t length() const`: Returns the number of key-value pairs in the JSON object. (Same as `size()`)

#### `empty()`

- `bool empty() const`: Checks if the JSON object is empty.

Example Usage 12: Checking if a JSON object is empty

```cpp
Json::JObject object;
if (object.empty()) {
    // JSON object is empty
}
```

#### `clear()`

- `void clear()`: Clears all key-value pairs from the JSON object.

Example Usage 13: Clearing a JSON object

```cpp
Json::JObject object = {"name", "Tom"};
object.clear();
```

## JArray Class

The JArray class is used to create and manipulate JSON arrays. Here are its member functions and usage:

### Construction

- `JArray()`: Creates an empty JSON array.
- `JArray(const std::vector<JValue>&& values)`: Creates a JSON array with specified values.

Example Usage 1: Creating an empty JSON array.

```cpp
Json::JArray array;
```

Example Usage 2: Creating a JSON array with multiple values.

```cpp
Json::JArray array({1, 2, 3, true, "null"});
```

### Adding Elements

JArray supports the following ways to add elements:

- `void append(const JValue& value)`: Adds an element to the end of the JSON array.
- `void pushBack(const JValue& value)`: Adds an element to the end of the JSON array. (Same as `append()`)
- `void pushFront(const JValue& value)`: Adds an element to the beginning of the JSON array.
- `void insert(size_t index, const JValue& value)`: Inserts an element at the specified position.
- `void insert(size_t index, const JArray& array)`: Inserts a JSON array at the specified position.
- `void insert(size_t index, const JObject& object)`: Inserts a JSON object at the specified position.

Example Usage 2: Adding multiple elements of different types at different positions

```cpp
Json::JArray array;
array.append(true);
array.pushBack(Json::JObject());
array.pushFront(123);
array.insert(1, "hello");
array.insert(2, Json::JArray());
```

After execution, the elements in `array` are: `[123, "hello", [], true, {}]`.

-------

JArray also provides the `<<` operator for adding elements:

- `JArray & operator<<(const JValue& value)`: Adds an element to the end of the JSON array using the `<<` operator.
- `JArray & operator<<(const JArray& array)`: Adds a JSON array to the end of the JSON array using the `<<` operator.
- `JArray & operator<<(const JObject& object)`: Adds a JSON object to the end of the JSON array using the `<<` operator.

Example Usage 3: Adding multiple elements of different types to the end of a JSON array using the `<<` operator

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
```

After execution, the elements in `array` are: `[true, {}, 123, "hello", []]`.

### Removing Elements

- `void remove(size_t index)`: Removes the element at the specified position from the JSON array.
- `void popBack()`: Removes an element from the end of the JSON array.
- `void popFront()`: Removes an element from the beginning of the JSON array.
- `void clear()`: Clears the JSON array, removing all elements.

Example Usage 4: Removing elements from a JSON array

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
array.remove(2);
array.popBack();
array.popFront();
```

After execution, the elements in `array` are: `[{}, "hello"]`.

### Accessing Elements

#### `toXXX()`

JArray also provides `toXXX()` methods for converting elements in the JSON array to different data types.

- `bool toBool(size_t index) const`: Converts the element at the specified position in the JSON array to a boolean value.
- `int32_t toInt(size_t index) const`: Converts the element at the specified position in the JSON array to a 32-bit integer.
- `int64_t toBigInt(size_t index) const`: Converts the element at the specified position in the JSON array to a 64-bit integer.
- `float toFloat(size_t index) const`: Converts the element at the specified position in the JSON array to a 32-bit floating point number.
- `double toDouble(size_t index) const`: Converts the element at the specified position in the JSON array to a 64-bit floating point number.
- `const std::string& toString(size_t index) const`: Converts the element at the specified position in the JSON array to a string.
- `const JArray* toArray(size_t index) const`: Converts the element at the specified position in the JSON array to an array.
- `const JObject* toObject(size_t index) const`: Converts the element at the specified position in the JSON array to an object.

For integer types, whether the JValue stores an `int32_t` or `int64_t`, you can use `toInt()` or `toBigInt()` to convert it to `int32_t` or `int64_t`. Similarly for floating point types.

> Note:
> 
> - When converting an `int64_t` value to `int32_t` using `toInt()`, higher-order bits may be lost.
> - When converting a `double` value to `float` using `toFloat()`, precision may be lost.

Example Usage 5: Accessing the third element in the array

```cpp
Json::JArray array;
array << 100 << 200 << 300 << 400 << 500;
int32_t thirdElement = array.toInt(2);
```

After execution, the value of `thirdElement` is `300`.

#### `operator[]`

- `JValue operator[](size_t index) const`: Returns the element at the specified position in the JSON array.

Example Usage 6: Accessing elements at specified positions in a JSON array

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
Json::JValue value = array[2];
```

After execution, the value of `value` is `123`.

### Other Methods

#### `size()`, `length()`

- `size_t size() const`: Returns the number of elements in the JSON array.
- `size_t length() const`: Returns the number of elements in the JSON array. (Same as `size()`)

#### `isNull()`

- `bool isNull(size_t index) const`: Checks if the element at the specified position in the JSON array is `null`.

#### `begin()`, `end()`

Non-const version:

- `iterator begin()`: Returns an iterator pointing to the beginning of the JSON array.
- `iterator end()`: Returns an iterator pointing to the end of the JSON array.

Const version:

- `constIterator begin() const`: Returns a const iterator pointing to the beginning of the JSON array.
- `constIterator end() const`: Returns a const iterator pointing to the end of the JSON array.

Example Usage 7: Iterating over all elements in a JSON array.

```cpp
for (auto it = array.begin(); it != array.end(); ++it) {
    Json::JValue value = *it;
    // Process value
}
```

Or you can use a range-based for loop to iterate over all elements in the JSON array:

```cpp
for (const auto& value : array) {
    // Process value
}
```

#### `sort()`

- `void sort(const std::function<bool(JValue&, JValue&)>& sort_function)`: Sorts the elements in the JSON array.

> Note:
> 
> - The sorting function `sort_function` must be a function object for comparing two `JValue` objects.
> - The sorting function `sort_function` must return a `bool` value indicating the relative order of the two `JValue` objects.

Example Usage 8: Sorting elements in a JSON array

```cpp
Json::JArray array;
array << 3 << 1 << 4 << 2 << 5;
array.sort([](Json::JValue& a, Json::JValue& b) {
    int v1 = std::get<int32_t>(a);
    int v2 = std::get<int32_t>(b);
    return v1 < v2;
});
```

After execution, the elements in `array` are: `[1, 2, 3, 4, 5]`.

## JValue

JValue is a type alias with the following type prototype:

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

JValue itself does not provide functions for converting or setting data types, but you can use `std::get()` to retrieve data types and `std::holds_alternative()` to check data types.

Example Usage 1: Checking if the data type of `value` is `int32_t`

```cpp
Json::JValue value = 123;
if (std::holds_alternative<int32_t>(value)) {
    int32_t intValue = std::get<int32_t>(value);
    // Process intValue
}
```

For data of type `JArray` or `JObject`, you can use the `std::get()` function to get the corresponding pointer and then use the pointer to access the data.

Example Usage 2: Getting the second element in `array`

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

## JGet Class

The JGet class is used to retrieve data from JValue objects. You can convert `JValue` objects to corresponding data types in the following ways:

- `JGet::toBool()`: Converts a `JValue` object to a boolean value.
- `JGet::toInt()`: Converts a `JValue` object to an integer value.
- `JGet::toBigInt()`: Converts a `JValue` object to a large integer value.
- `JGet::toFloat()`: Converts a `JValue` object to a floating point value.
- `JGet::toString()`: Converts a `JValue` object to a string.
- `JGet::toArray()`: Converts a `JValue` object to a JSON array pointer.
- `JGet::toObject()`: Converts a `JValue` object to a JSON object pointer.

Additionally, the JGet class provides functions to check data types, which you can use to determine the specific data type of a `JValue` object.

- `JGet::isNull()`: Checks if a `JValue` object is `null`.
- `JGet::isBool()`: Checks if a `JValue` object is a boolean value.
- `JGet::isInt()`: Checks if a `JValue` object is an integer value.
- `JGet::isBigInt()`: Checks if a `JValue` object is a large integer value.
- `JGet::isFloat()`: Checks if a `JValue` object is a floating point value.
- `JGet::isDouble()`: Checks if a `JValue` object is a double precision floating point value.
- `JGet::isString()`: Checks if a `JValue` object is a string.
- `JGet::isArray()`: Checks if a `JValue` object is a JSON array.
- `JGet::isObject()`: Checks if a `JValue` object is a JSON object.

Here are some example usages of the JGet class:

Example Usage 1: Converting a `JValue` object to a string

```cpp
Json::JValue value = "hello";
std::string str = Json::JGet::toString(value);
```

After execution, the value of `str` is `"hello"`.

Example Usage 2: Converting a `JValue` object to a `JArray` object and iterating over all elements

```cpp
Json::JArray array({1, 2, 3, true, "null"});
for (auto& v : array) {
    if (Json::JGet::isInt(v))
        std::cout << Json::JGet::toInt(v) << " ";
    else if (Json::JGet::isBool(v))
        std::cout << (Json::JGet::toBool(v) ? "true" : "false") << " ";
    else if (Json::JGet::isString(v))
        std::cout << Json::JGet::toString(v) << " ";
    // Note: This example only handles three data types, you can add other check logic as needed
}
```

After execution, the output is:

```
null
```

## JParser Class

The JParser class is used to generate and parse JSON data. Here are its member functions and usage:

### Construction

- `JParser()`: Creates an empty JParser object.
- `JParser(const std::string& file_name, size_t max_cols_inline = 1024)`: Creates a JParser object and loads data from the specified JSON file. Reads at most `max_cols_inline` characters per line (default is 1024 characters per line).
- `JParser(const JObject& root_object)`: Creates a JParser object and initializes data using the specified JSON object.
- `JParser(const JArray& root_array)`: Creates a JParser object and initializes data using the specified JSON array.

Example Usage 1: Loading data from the `config.json` file and setting a maximum of 127 characters per line.

```cpp
Json::JParser parser("config.json", 127);
```

Example Usage 2: Initializing data using a JSON object

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
```

### Parsing Data

The JParser class provides the following methods for parsing JSON data:

#### `parse()`

- `void parse(const std::string& json)`: Parses the specified JSON string.

Example Usage 1: Parsing data from a JSON string and getting a list of object keys

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

After execution, the output is:
```
["key1", "key2", "key3", "array"]
```

#### `parseFromJsonFile()`

- `bool parseFromJsonFile(const std::string& file_name, size_t max_cols_inline = 1024)`: Loads and parses data from the specified JSON file. Reads at most `max_cols_inline` characters per line (default is 1024 characters per line).

Example Usage 2: Loading and parsing data from the `config.json` file

```cpp
Json::JParser parser;
bool is_success = parser.parseFromJsonFile("config.json");
if (is_success) {
    // Parsed successfully
} else {
    // Failed to parse JSON file
}
```

### Generating Data

The JParser class provides the following methods for generating JSON data:

#### `dump()`

- `std::string dump(size_t indent = 2)`: Converts JSON data to a string.

Example Usage 1: Converting a JSON object to a string

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
std::string json = parser.dump(4);
std::cout << json << std::endl;
```

After execution, the output is:
```json
{
    "key1": "value1",
    "key2": "value2",
    "key3": "value3"
}
```

Example Usage 2: Converting a JSON array to a string

```cpp
Json::JArray array;
array << 1 << 2 << 3 << 4 << 5;

Json::JParser parser(array);
std::string json = parser.dump(4);
std::cout << json << std::endl;
```

After execution, the output is:
```json
[
    1,
    2,
    3,
    4,
    5
]
```

Example Usage 3: Adding some empty arrays, empty objects, and null values to a JSON object

```cpp
Json::JObject obj;
obj["null"] = std::monostate{};
obj["null_object"] = Json::JObject();
obj["null_array"] = Json::JArray();

Json::JParser parser(obj);
parser.dump(4);
```

The content of the output `config.json` file is as follows:

```json
{
    "null": null,
    "null_object": {},
    "null_array": []
}
```

#### `dumpToJsonFile()`

- `bool dumpToJsonFile(const std::string& file_name, size_t indent = 2)`: Converts JSON data to a string and writes it to the specified JSON file.

Example Usage 1: Converting a JSON object to a string and writing it to the `config.json` file

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
parser.dumpToJsonFile("config.json", 4);
```

The content of the output `config.json` file is as follows:

```json
{
    "key1": "value1",
    "key2": "value2",
    "key3": "value3"
}
```

Example Usage 2: Converting a JSON array to a string and writing it to the `config.json` file

```cpp
Json::JArray array;
array << 1 << 2 << 3 << 4 << 5;

Json::JParser parser(array);
parser.dumpToJsonFile("config.json", 4);
```

The content of the output `config.json` file is as follows:

```json
[
    1,
    2,
    3,
    4,
    5
]
```

Example Usage 3: Adding some empty arrays, empty objects, and null values to a JSON object

```cpp
Json::JObject obj;
obj["null"] = std::monostate{};
obj["null_object"] = Json::JObject();
obj["null_array"] = Json::JArray();

Json::JParser parser(obj);
parser.dumpToJsonFile("config.json", 4);
```

The content of the output `config.json` file is as follows:

```json
{
    "null": null,
    "null_object": {},
    "null_array": []
}
```

### Setting Root Object or Root Array

The JParser class provides the following methods to set the root object or root array:

#### `setRootObject()`

- `void setRootObject(JObject& object)`: Sets the root object of the parser to the specified JSON object.

#### `setRootArray()`

- `void setRootArray(JArray& array)`: Sets the root array of the parser to the specified JSON array.

It also provides the following methods to get the current root object or root array:

#### `object()`

- `const JObject& object() const`: Returns the current root object of the parser.

#### `array()`

- `const JArray& array() const`: Returns the current root array of the parser.

# Learn More

- [Usage](usage.md)
- [Examples](example.md)
- [Building JsonBuilder with CMake](cmake.md)