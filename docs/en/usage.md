# JsonBuilder Usage Guide

JsonBuilder is a C++ library for building JSON data. It provides a simple and easy-to-use API for creating, parsing, and manipulating JSON data.

## Installation

### Direct Import [Simplest]

JsonBuilder can be directly imported into the project without installation.

Clone the JsonBuilder repository using the following Git directory:
```bash
git clone https://github.com/CatIsNotFound/JsonBuilder.git  
cd JsonBuilder
```

Copy the `Json.h` and `Json.cpp` files from the `src` directory in the project root to your project directory.

### Installing Release Binary Version

JsonBuilder can be downloaded from the latest release version on [repository](https://github.com/CatIsNotFound/JsonBuilder/releases/latest) on GitHub.

### Manual Compilation

Clone the JsonBuilder repository using the following Git directory:
```bash
git clone https://github.com/CatIsNotFound/JsonBuilder.git  
cd JsonBuilder
```

You can configure the project and compile it using CMake. For specific methods, please refer to [Building JsonBuilder with CMake](cmake.md).

## Importing the Library

In your C++ project, include the `Json.h` file to use the JsonBuilder library.

```cpp
#include "path/to/JsonBuilder/Json.h"
```

## Brief Examples

Here are two examples showing how to use the JsonBuilder library to create and manipulate JSON data.

```cpp
#include <JsonBuilder/Json.h>  // Include JsonBuilder library header file
#include "/path/to/Json.h"     // Use JsonBuilder library through Json.h header file

using namespace JsonBuilder;

int main() {
    // Create a JSON array
    JArray array;
    array << 1 << 2 << 3;

    // Create a JSON object
    JObject object;
    object["name"] = "John Doe";
    object["age"] = 30;
    object["array"] = array;

    // Create a JSON parser
    JParser parser;
    parser.setRootObject(object);

    // Print JSON string representation of the parser
    std::cout << parser.dump(4) << std::endl;

    return 0;
}
```

After executing the above example code, the following JSON string will be displayed in the terminal:
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

For more examples, you can refer to [JsonBuilder Usage Examples](example.md).

For more JsonBuilder class-related references, please refer to [JsonBuilder Class Reference](class.md).