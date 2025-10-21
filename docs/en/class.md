# JsonBuilder Class Reference

The JsonBuilder library includes the following classes:

- JsonBuilder (namespace)
    - `JObject`: Object class
    - `JArray`: Array class
    - `JValue`: Value class
    - `JParser`: JSON parser class
    - `JGet`: Get data from `JValue`
    - `JDataType`: Data type enumeration
        - `Null` - represented by `std::monostate`
        - `Bool` - `true` or `false`
        - `Int` - 32-bit integer
        - `BigInt` - 64-bit integer
        - `Float` - 32-bit floating point
        - `Double` - 64-bit floating point
        - `String` - UTF-8 encoded string
        - `Array` - ordered collection of values
        - `Object` - unordered collection of key-value pairs
    - `JException`: Exception namespace
        - `KeyIsNotFoundException`: Key not found exception (usually occurs when accessing a non-existent key in an object)
        - `GetBadValueException`: Get bad value exception (usually occurs when trying to convert a value to an incompatible type)
        - `ParseJsonError`: Parse JSON error (usually occurs when the JSON text format is incorrect)

## JObject Class

The JObject class is used to create and manipulate JSON objects. Here are the member functions and usage of the JObject class:

### Constructors

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

Example Usage 2: Continuing from Example Usage 1, create a key-value pair with key "address" and value as a nested object.

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

Of course, you can also use `operator[]` to set the value of an existing key. This won't be elaborated further here.

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

JObject provides the following methods to convert JSON objects to other data types:

- `bool toBool(const std::string& key) const`: Converts the key in the JSON object to a boolean value.
- `int32_t toInt(const std::string& key) const`: Converts the key in the JSON object to a 32-bit integer.
- `int64_t toBigInt(const std::string& key) const`: Converts the key in the JSON object to a 64-bit integer.
- `float toFloat(const std::string& key) const`: Converts the key in the JSON object to a 32-bit floating point number.
- `double toDouble(const std::string& key) const`: Converts the key in the JSON object to a 64-bit floating point number.
- `std::string toString(const std::string& key) const`: Converts the JSON object to a string.
- `JArray toArray(const std::string& key) const`: Converts the JSON object to an array.
- `JObject toObject(const std::string& key) const`: Converts the JSON object to an object.

For stored integer type data, regardless of whether `JValue` stores `int32_t` or `int64_t`, you can use the `toInt()` or `toBigInt()` methods to convert it to `int32_t` or `int64_t` type.
For stored floating point type data, regardless of whether `JValue` stores `float` or `double`, you can use the `toFloat()` or `toDouble()` methods to convert it to `float` or `double` type.

> Note:
>
> - When using the `toInt()` method to convert a value of type `int64_t` to type `int32_t`, high-order data may be lost.
> - When using the `toFloat()` method to convert a value of type `double` to type `float`, precision loss may occur.

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
    // process value
}
```

Or you can use a range-based loop:

```cpp
for (const auto& value : object) {
    // process value
}
```

#### `size()`

The `size_t size() const` method returns the number of key-value pairs contained in the JSON object.

#### `valid()`

The `bool valid(const std::string& key) const` method checks if the specified key exists in the JSON object.

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

The `void clear()` method clears the JSON object, deleting all key-value pairs.

Example Usage 12: Clear the JSON object.

```cpp
object.clear();
```

## JArray Class

The JArray class is used to create and manipulate JSON arrays. Here are the member functions and usage of the JArray class:

### Constructors

- `JArray()`: Creates an empty JSON array.
- `JArray(const std::vector<JValue>&& values)`: Creates a JSON array containing the specified values.

Example Usage 1: Create an empty JSON array.

```cpp
Json::JArray array;
```

Example Usage 2: Create a JSON array containing multiple values.

```cpp
Json::JArray array({1, 2, 3, true, "null"});
```

### Adding Elements

The JArray class supports the following ways to add elements:

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
`void clear()`: Clears the JSON array, deleting all elements.

Example Usage 4: Remove elements at specified positions from the JSON array

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

The JArray class also provides `toXXX()` methods for converting an element in the JSON array to values of different data types.

- `bool toBool(size_t index) const`: Converts the element at the specified position in the JSON array to a boolean value.
- `int32_t toInt(size_t index) const`: Converts the element at the specified position in the JSON array to a 32-bit integer.
- `int64_t toBigInt(size_t index) const`: Converts the element at the specified position in the JSON array to a 64-bit integer.
- `float toFloat(size_t index) const`: Converts the element at the specified position in the JSON array to a 32-bit floating point number.
- `double toDouble(size_t index) const`: Converts the element at the specified position in the JSON array to a 64-bit floating point number.
- `const std::string& toString(size_t index) const`: Converts the element at the specified position in the JSON array to a string.
- `const JArray* toArray(size_t index) const`: Converts the element at the specified position in the JSON array to an array.
- `const JObject* toObject(size_t index) const`: Converts the element at the specified position in the JSON array to an object.

For stored integer type data, regardless of whether `JValue` stores `int32_t` or `int64_t`, you can use the `toInt()` or `toBigInt()` methods to convert it to `int32_t` or `int64_t` type.
For stored floating point type data, regardless of whether `JValue` stores `float` or `double`, you can use the `toFloat()` or `toDouble()` methods to convert it to `float` or `double` type.

> Note:
>
> - When using the `toInt()` method to convert a value of type `int64_t` to type `int32_t`, high-order data may be lost.
> - When using the `toFloat()` method to convert a value of type `double` to type `float`, precision loss may occur.

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
    // process value
}
```

Or you can use a range-based `for` loop to iterate through all elements in the JSON array:

```cpp
for (const auto& value : array) {
    // process value
}
```

#### `sort()`

- `void sort(const std::function<bool(JValue&, JValue&)>& sort_function)`: Sorts the elements in the JSON array.

> Note:
>
> - The sorting function `sort_function` must be a function object used to compare the sizes of two `JValue` objects.
> - The sorting function `sort_function` must return a value of type `bool` to indicate the relative order of the two `JValue` objects.

Example Usage 8: Sort the elements in the JSON array

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

Example Usage 1: Determine if the data type of `value` is `int32_t`

```cpp
Json::JValue value = 123;
if (std::holds_alternative<int32_t>(value)) {
    int32_t intValue = std::get<int32_t>(value);
    // process intValue
}
```

For data of type `JArray` or `JObject`, you can obtain the corresponding pointer through the `std::get()` function, and then use the pointer to access the data.

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

## JGet Class

The JGet class is used to get data from JValue objects. You can convert `JValue` objects to corresponding data types in the following ways:

- `JGet::toBool()`: Converts the `JValue` object to a boolean value.
- `JGet::toInt()`: Converts the `JValue` object to an integer value.
- `JGet::toBigInt()`: Converts the `JValue` object to a big integer value.
- `JGet::toFloat()`: Converts the `JValue` object to a floating point value.
- `JGet::toString()`: Converts the `JValue` object to a string.
- `JGet::toArray()`: Converts the `JValue` object to a JSON array pointer.
- `JGet::toObject()`: Converts the `JValue` object to a JSON object pointer.

In addition, the JGet class also provides functions to determine data types, you can use these functions to determine the specific data type of the `JValue` object.

- `JGet::isNull()`: Determines if the `JValue` object is `null`.
- `JGet::isBool()`: Determines if the `JValue` object is a boolean value.
- `JGet::isInt()`: Determines if the `JValue` object is an integer value.
- `JGet::isBigInt()`: Determines if the `JValue` object is a big integer value.
- `JGet::isFloat()`: Determines if the `JValue` object is a floating point value.
- `JGet::isDouble()`: Determines if the `JValue` object is a double-precision floating point value.
- `JGet::isString()`: Determines if the `JValue` object is a string.
- `JGet::isArray()`: Determines if the `JValue` object is a JSON array.
- `JGet::isObject()`: Determines if the `JValue` object is a JSON object.

The following are example usages of the JGet class:

Example Usage 1: Convert a `JValue` object to a string

```cpp
Json::JValue value = "hello";
std::string str = Json::JGet::toString(value);
```

After execution, the value of the `str` variable is `"hello"`.

Example Usage 2: Convert a `JValue` object to a `JArray` object and iterate through all elements

```cpp
Json::JArray array({1, 2, 3, true, "null"});
for (auto& v : array) {
    if (Json::JGet::isInt(v))
        std::cout << Json::JGet::toInt(v) << " ";
    else if (Json::JGet::isBool(v))
        std::cout << (Json::JGet::toBool(v) ? "true" : "false") << " ";
    else if (Json::JGet::isString(v))
        std::cout << Json::JGet::toString(v) << " ";
    // p.s: Only three data types are handled in the example, you can add other judgment logic as needed
}
```

After execution, the output result is:

```
null
```

## JParser Class

The JParser class is used to generate and parse JSON data. Here are the member functions and usage of the JParser class:

### Constructors

- `JParser()`: Creates an empty JParser object.
- `JParser(const std::string& file_name, size_t max_cols_inline = 1024)`: Creates a JParser object and loads data from the specified JSON file. Each line reads up to `max_cols_inline` characters (default maximum 1024 characters per line).
- `JParser(const JObject& root_object)`: Creates a JParser object and initializes data using the specified JSON object.
- `JParser(const JArray& root_array)`: Creates a JParser object and initializes data using the specified JSON array.

Example Usage 1: Load data from the `config.json` file and set a maximum of 127 characters per line.

```cpp
Json::JParser parser("config.json", 127);
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

The JParser class provides the following methods to parse JSON data:

#### `parse()`

`void parse(const std::string& json)`: Parses the specified JSON string.

Example Usage 1: Parse data from a JSON string and get the object's key list

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

`bool parseFromJsonFile(const std::string& file_name, size_t max_cols_inline = 1024)`: Loads and parses data from the specified JSON file. Each line reads up to `max_cols_inline` characters (default maximum 1024 characters per line).

Example Usage 2: Load and parse data from the `config.json` file

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

The JParser class provides the following methods to generate JSON data:

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

The JParser class provides the following methods to set the root object or root array:

#### `setRootObject()`

`void setRootObject(JObject& object)`: Sets the root object of the parser to the specified JSON object.

#### `setRootArray()`

`void setRootArray(JArray& array)`: Sets the root array of the parser to the specified JSON array.

At the same time, the following methods are also provided to obtain the current root object or root array:

#### `object()`

`const JObject& object() const`: Returns the current root object of the parser.

#### `array()`

`const JArray& array() const`: Returns the current root array of the parser.

# Learn More

- [Usage Guide](usage.md)
- [Examples](example.md)
- [Building JsonBuilder with CMake](cmake.md)