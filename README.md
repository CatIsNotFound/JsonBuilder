# JsonBuilder

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg) ![License](https://img.shields.io/badge/License-MIT-green.svg)

A lightweight and efficient C++ JSON parsing and manipulation library.

## Features

- Complete JSON data type support: null, boolean, integer, floating-point, string, array, and object
- Easy-to-use API for creating, parsing, and manipulating JSON data
- File I/O support for loading and saving JSON files
- Custom exception handling for robust error management
- Supports nested structures and complex JSON manipulation
- Efficient parsing and serialization

## Installation

**⚠️ NOTE**: This library is designed for **C++20** and above.


1. Copy the `src` directory into your project.

2. Include the source files in your project:
    ```cpp
    #include "src/Json.h"
    ```

## Basic Usage

### Parsing JSON from File

```cpp
Json::JParser parser;
parser.parseFromJsonFile("simple.json");
```

### Accessing JSON Data

```cpp
// Access array elements
const auto& array = parser.array();
std::string name = array.toString(0);

// Access object properties
const auto& object = parser.object();
bool flag = object.toBool("active");
int value = object.toInt("id");
std::string text = object.toString("description");
```

### Creating JSON Data

```cpp
// Create a JSON object
Json::JObject person;
person.set("name", "John Doe");
person.set("age", 30);
person.set("isEmployed", true);

// Create a JSON array
Json::JArray hobbies;
hobbies.pushBack("reading");
hobbies.pushBack("gaming");
hobbies.pushBack("coding");

// Add array to object
person.set("hobbies", hobbies);

// Create parser with object
Json::JParser parser(person);
```

### Serializing JSON

```cpp
// Dump to string
std::string jsonString = parser.dump(2);  // 2 spaces for indentation

// Save to file
parser.dumpToJsonFile("output.json", 2);
```

## Data Types

The library supports the following JSON data types:

- `null` - represented by `std::monostate`
- `boolean` - `true` or `false`
- `integer` - 32-bit integer
- `bigint` - 64-bit integer
- `float` - 32-bit floating point
- `double` - 64-bit floating point
- `string` - UTF-8 encoded string
- `array` - ordered collection of values
- `object` - unordered collection of key-value pairs

## Error Handling

The library uses exceptions for error handling:

- `KeyIsNotFoundException` - Thrown when trying to access a non-existent key in an object
- `GetBadValueException` - Thrown when trying to convert a value to an incompatible type
- `ParseJsonError` - Thrown when there's an error parsing JSON text

```cpp
try {
    std::string value = object.toString("nonExistentKey");
} catch (const Json::KeyIsNotFoundException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests.

## License

This project is licensed under the [MIT License](LICENSE).