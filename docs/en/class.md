# JsonBuilder Class Reference

The JsonBuilder library contains the following classes:

- JsonBuilder (namespace)
    - `JObject`: Object class
    - `JArray`: Array class
    - `JValue`: Value class
    - `JDataType`: Data type enumeration
    - `JException`: Exception namespace
        - `KeyIsNotFoundException`: Key not found exception (usually occurs when accessing a non-existent key in an object)
        - `GetBadValueException`: Get bad value exception (usually occurs when trying to convert a value to an incompatible type)
        - `ParseJsonError`: Parse JSON error (usually occurs when JSON text format is incorrect)

## JObject Class

JObject class is used to create and manipulate JSON objects. Here are the member functions and usage of JObject class:

### Constructor

`JObject()`: Creates an empty JSON object.

Usage:

```cpp
Json::JObject object;
```

### Setting Key-Value Pairs

#### `set()`

`void set(const std::string& key, const JValue& value)`: Sets a key-value pair in the JSON object.

Example Usage 1: Create a key-value pair with key "name" and value "John Doe".

```cpp
object.set("name", Json::JValue("John Doe"));
```

To create a nested object, use the `JObject` constructor.

Example Usage 2: Continuing from Example 1, create another key-value pair with key "address" and value as a nested object.

```cpp
Json::JObject addressObject;
addressObject.set("city", Json::JValue("New York"));
object.set("address", addressObject);
```

#### `operator[]`

`JValue& operator[](const std::string& key)`: Accesses a value in the JSON object by key.

Example Usage 3: Use `operator[]` to create an "age" key and set its value to 30.

```cpp
object["age"] = Json::JValue(30);
```

Of course, you can also use `operator[]` to set an existing key and its value. No more details here.

### Getting Key-Value Pairs

#### `get()`

`JValue & get(const std::string& key)`: Gets the value of a specified key in the JSON object.

Example Usage 4: Get the value corresponding to the "name" key.

```cpp
Json::JValue nameValue = object.get("name");
```

#### `operator[]`

`JValue& operator[](const std::string& key)`: Accesses a value in the JSON object by key.

Example Usage 5: Use `operator[]` to get the value corresponding to the "age" key.

```cpp
Json::JValue ageValue = object["age"];
int age = std::get<int32_t>(ageValue);
```

#### `toXXX()`

JObject provides the following methods to convert a JSON object to other data types:

- `bool toBool(const std::string& key) const`: Converts a key in the JSON object to a boolean value.
- `int32_t toInt(const std::string& key) const`: Converts a key in the JSON object to a 32-bit integer.
- `int64_t toBigInt(const std::string& key) const`: Converts a key in the JSON object to a 64-bit integer.
- `float toFloat(const std::string& key) const`: Converts a key in the JSON object to a 32-bit floating point number.
- `double toDouble(const std::string& key) const`: Converts a key in the JSON object to a 64-bit floating point number.
- `std::string toString(const std::string& key) const`: Converts a JSON object to a string.
- `JArray toArray(const std::string& key) const`: Converts a JSON object to an array.
- `JObject toObject(const std::string& key) const`: Converts a JSON object to an object.

For integer value types, whether stored as `int32_t` or `int64_t` in `JValue`, you can use `toInt()` or `toBigInt()` methods to convert them to `int32_t` or `int64_t` types.
For floating point value types, whether stored as `float` or `double` in `JValue`, you can use `toFloat()` or `toDouble()` methods to convert them to `float` or `double` types.

> Note:
>
> - When using the `toInt()` method to convert an `int64_t` type value to an `int32_t` type, high-order data may be lost.
> - When using the `toFloat()` method to convert a `double` type value to a `float` type, precision loss may occur.

Example Usage 6: Convert the value corresponding to the "age" key to a 32-bit integer.

```cpp
int32_t age = object.toInt("age");
```

### Other Functions

#### `keys()`

`std::vector<std::string> keys() const`: Gets a list of all keys in the JSON object.

Example Usage 7: Get a list of all keys in the JSON object.

```cpp
std::vector<std::string> keyList = object.keys();
```

#### `isNull()`

`bool isNull(const std::string& key) const`: Checks if the specified key in the JSON object is `null`.

Example Usage 8: Check if the "name" key is `null`.

```cpp
bool isNameNull = object.isNull("name");
```

#### `begin()`, `end()`

Non-`const` version:

- `std::vector<JValue>::iterator begin()`: Returns an iterator pointing to the first value in the JSON object.
- `std::vector<JValue>::iterator end()`: Returns an iterator pointing to the last value in the JSON object.

`const` version:

- `std::vector<JValue>::constIterator begin() const`: Returns an iterator pointing to the first value in the JSON object.
- `std::vector<JValue>::constIterator end() const`: Returns an iterator pointing to the last value in the JSON object.

Example Usage 9: Iterate through all values in the JSON object.

```cpp
for (auto it = object.begin(); it != object.end(); ++it) {
    Json::JValue value = *it;
    // Process value
}
```

Or you can use a range-based loop:

```cpp
for (const auto& value : object) {
    // Process value
}
```

#### `size()`

The `size_t size() const` method returns the number of key-value pairs contained in the JSON object.

#### `valid()`

The `bool valid(const std::string& key) const` method checks if a specified key exists in the JSON object.

Example Usage 10: Check if the "age" key exists.

```cpp
bool isAgeValid = object.valid("age");
```

#### `remove()`

The `void remove(const std::string& key)` method deletes the key-value pair corresponding to the specified key in the JSON object.

Example Usage 11: Delete the key-value pair corresponding to the "age" key.

```cpp
object.remove("age");
```

#### `clear()`

The `void clear()` method empties the JSON object, deleting all key-value pairs.

Example Usage 12: Empty the JSON object.

```cpp
object.clear();
```

## JArray Class

JArray class is used to create and manipulate JSON arrays. Here are the member functions and usage of JArray class:

### Constructor

`JArray()`: Creates an empty JSON array.

Example Usage 1: Create an empty JSON array.

```cpp
Json::JArray array;
```

### Adding Elements

JArray class supports the following ways to add elements:

- `void append(const JValue& value)`: Adds an element to the end of the JSON array.
- `void pushBack(const JValue& value)`: Adds an element to the end of the JSON array. (Same as `append()` function)
- `void pushFront(const JValue& value)`: Adds an element to the beginning of the JSON array.
- `void insert(size_t index, const JValue& value)`: Inserts an element at the specified position.
- `void insert(size_t index, const JArray& array)`: Inserts a JSON array at the specified position.
- `void insert(size_t index, const JObject& object)`: Inserts a JSON object at the specified position.

Example Usage 2: Add multiple elements of different types to the JSON array at different positions

```cpp
Json::JArray array;
array.append(true);
array.pushBack(Json::JObject());
array.pushFront(123);
array.insert(1, "hello");
array.insert(2, Json::JArray());
```

After execution, the elements in the `array` array are: `[123, "hello", [], true, {}]`.

-------

JArray also provides a way to add elements based on the `<<` operator:

`JArray & operator<<(const JValue& value)`: Use the `<<` operator to add an element to the end of the JSON array.
`JArray & operator<<(const JArray& array)`: Use the `<<` operator to add a JSON array to the end of the JSON array.
`JArray & operator<<(const JObject& object)`: Use the `<<` operator to add a JSON object to the end of the JSON array.

Example Usage 3: Use the `<<` operator to add multiple elements of different types to the end of the JSON array

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
```

After execution, the elements in the `array` array are: `[true, {}, 123, "hello", []]`.

### Removing Elements

`void remove(size_t index)`: Removes the element at the specified position from the JSON array.
`void popBack()`: Removes an element from the end of the JSON array.
`void popFront()`: Removes an element from the beginning of the JSON array.
`void clear()`: Empties the JSON array, deleting all elements.

Example Usage 4: Remove elements from the JSON array at specified positions

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
array.remove(2);
array.popBack();
array.popFront();
```

After execution, the elements in the `array` array are: `[{}, "hello"]`.

### Accessing Elements

#### `toXXX()`

JArray class also provides `toXXX()` methods for converting an element in the JSON array to different data types.

- `bool toBool(size_t index) const`: Converts the element at the specified position in the JSON array to a boolean value.
- `int32_t toInt(size_t index) const`: Converts the element at the specified position in the JSON array to a 32-bit integer.
- `int64_t toBigInt(size_t index) const`: Converts the element at the specified position in the JSON array to a 64-bit integer.
- `float toFloat(size_t index) const`: Converts the element at the specified position in the JSON array to a 32-bit floating point number.
- `double toDouble(size_t index) const`: Converts the element at the specified position in the JSON array to a 64-bit floating point number.
- `const std::string& toString(size_t index) const`: Converts the element at the specified position in the JSON array to a string.
- `const JArray* toArray(size_t index) const`: Converts the element at the specified position in the JSON array to an array.
- `const JObject* toObject(size_t index) const`: Converts the element at the specified position in the JSON array to an object.

For integer value types, whether stored as `int32_t` or `int64_t` in `JValue`, you can use `toInt()` or `toBigInt()` methods to convert them to `int32_t` or `int64_t` types.
For floating point value types, whether stored as `float` or `double` in `JValue`, you can use `toFloat()` or `toDouble()` methods to convert them to `float` or `double` types.

> Note:
>
> - When using the `toInt()` method to convert an `int64_t` type value to an `int32_t` type, high-order data may be lost.
> - When using the `toFloat()` method to convert a `double` type value to a `float` type, precision loss may occur.

Example Usage 5: Access the 3rd element in the array

```cpp
Json::JArray array;
array << 100 << 200 << 300 << 400 << 500;
int32_t thirdElement = array.toInt(2);
```

After execution, the value of the `thirdElement` variable is `300`.

#### `operator[]`

`JValue operator[](size_t index) const`: Returns the element at the specified position in the JSON array.

Example Usage 6: Access the element at the specified position in the JSON array

```cpp
Json::JArray array;
array << true << Json::JObject() << 123 << "hello" << Json::JArray();
Json::JValue value = array[2];
```

After execution, the value of the `value` variable is `123`.

### Other Functions

#### `size()`, `length()`

- `size_t size() const`: Returns the number of elements contained in the JSON array.
- `size_t length() const`: Returns the number of elements contained in the JSON array. (Same as `size()` function)

#### `isNull()`

- `bool isNull(size_t index) const`: Checks if the element at the specified position in the JSON array is `null`.

#### `begin()`, `end()`

Non-`const` version:

- `iterator begin()`: Returns an iterator pointing to the beginning of the JSON array.
- `iterator end()`: Returns an iterator pointing to the end of the JSON array.

`const` version:

- `constIterator begin() const`: Returns an iterator pointing to the beginning of the JSON array.
- `constIterator end() const`: Returns an iterator pointing to the end of the JSON array.

Example Usage 7: Iterate through all elements in the JSON array.

```cpp
for (auto it = array.begin(); it != array.end(); ++it) {
    Json::JValue value = *it;
    // Process value
}
```

Or you can use a range-based `for` loop to iterate through all elements in the JSON array:

```cpp
for (const auto& value : array) {
    // Process value
}
```

#### `sort()`

- `void sort(const std::function<bool(JValue&, JValue&)>& sort_function)`: Sorts the elements in the JSON array.

> Note:
>
> - The sorting function `sort_function` must be a function object for comparing the sizes of two `JValue` objects.
> - The sorting function `sort_function` must return a `bool` type value indicating the relative order of the two `JValue` objects.

Example Usage 8: Sort elements in the JSON array

```cpp
Json::JArray array;
array << 3 << 1 << 4 << 2 << 5;
array.sort([](Json::JValue& a, Json::JValue& b) {
    int v1 = std::get<int32_t>(a);
    int v2 = std::get<int32_t>(b);
    return v1 < v2;
});
```

After execution, the elements in the `array` array are: `[1, 2, 3, 4, 5]`.

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

JValue itself does not provide functions for converting data types or setting data types, but you can use the `std::get()` function to obtain data types and use the `std::holds_alternative()` function to determine data types.

Example Usage 1: Determine if the data type of `value` is `int32_t` type

```cpp
Json::JValue value = 123;
if (std::holds_alternative<int32_t>(value)) {
    int32_t intValue = std::get<int32_t>(value);
    // Process intValue
}
```

For data of `JArray` or `JObject` type, you can obtain the corresponding pointer through the `std::get()` function, and then use the pointer to access the data.

Example Usage 2: Get the second element in `array`

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

## JParser Class

JParser class is used to generate and parse JSON data. Here are the member functions and usage of JParser class:

### Constructor

- `JParser()`: Creates an empty JParser object.
- `JParser(const std::string& file_name)`: Creates a JParser object and loads data from the specified JSON file.
- `JParser(const JObject& root_object)`: Creates a JParser object and initializes data using the specified JSON object.
- `JParser(const JArray& root_array)`: Creates a JParser object and initializes data using the specified JSON array.

Example Usage 1: Load data from the `config.json` file

```cpp
Json::JParser parser("config.json");
```

Example Usage 2: Initialize data using a JSON object

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
```

### Parsing Data

JParser class provides the following methods for parsing JSON data:

#### `parse()`

`void parse(const std::string& json)`: Parses the specified JSON string.

Example Usage 1: Parse data from a JSON string and get the key list of the object

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

After execution, the output result is:
```
["key1", "key2", "key3", "array"]
```

#### `parseFromJsonFile()`

`bool parseFromJsonFile(const std::string& file_name)`: Loads data from the specified JSON file and parses it.

Example Usage 2: Load data from the `config.json` file and parse it

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

JParser class provides the following methods for generating JSON data:

#### `dump()`

`std::string dump(size_t indent = 2)`: Converts JSON data to a string.

Example Usage 1: Convert a JSON object to a string

```cpp
Json::JObject object;
object["key1"] = "value1";
object["key2"] = "value2";
object["key3"] = "value3";

Json::JParser parser(object);
std::string json = parser.dump(4);
std::cout << json << std::endl;
```

After execution, the output result is:
```json
{
    "key1": "value1",
    "key2": "value2",
    "key3": "value3"
}
```

Example Usage 2: Convert a JSON array to a string

```cpp
Json::JArray array;
array << 1 << 2 << 3 << 4 << 5;

Json::JParser parser(array);
std::string json = parser.dump(4);
std::cout << json << std::endl;
```

After execution, the output result is:
```json
[
    1,
    2,
    3,
    4,
    5
]
```

Example Usage 3: Add some empty arrays, empty objects, and null values to a JSON object

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

`bool dumpToJsonFile(const std::string& file_name, size_t indent = 2)`: Converts JSON data to a string and writes it to the specified JSON file.

Example Usage 1: Convert a JSON object to a string and write it to the `config.json` file

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

Example Usage 2: Convert a JSON array to a string and write it to the `config.json` file

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

Example Usage 3: Add some empty arrays, empty objects, and null values to a JSON object

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

JParser class provides the following methods to set the root object or root array:

#### `setRootObject()`

`void setRootObject(JObject& object)`: Sets the root object of the parser to the specified JSON object.

#### `setRootArray()`

`void setRootArray(JArray& array)`: Sets the root array of the parser to the specified JSON array.

At the same time, the following methods are provided to obtain the current root object or root array:

#### `object()`

`const JObject& object() const`: Returns the current root object of the parser.

#### `array()`

`const JArray& array() const`: Returns the current root array of the parser.

# Learn More

- [Usage](usage.md)
- [Examples](example.md)
- [Building JsonBuilder with CMake](cmake.md)