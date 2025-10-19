# JsonBuilder

[简体中文](README_zh.md)

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

**⚠️ NOTE**: This library is only applicable to the **C++20** standard and above.

1. [Click to download the latest release.](https://github.com/CatIsNotFound/JsonBuilder/releases/latest)
2. Clone this repo:
   ```bash
   git clone https://github.com/CatIsNotFound/JsonBuilder.git
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

## Learn more

- [Usage](docs/usage.md)
- [Example](docs/example.md)
- [How to build with CMake?](docs/cmake-build.md)

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests.

## License

This project is licensed under the [MIT License](LICENSE).