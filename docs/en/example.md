# JsonBuilder Usage Examples

## Example 1: Personal Information

The following example creates a JSON object containing personal information:

```cpp
#include <JsonBuilder/Json.h> // Assuming using static/dynamic library

int main() {
    // Create a JSON object to store personal information
    Json::JObject person;
    // Add personal information
    person.set("name", "Alice");
    person.set("age", 18);
    person.set("gender", "female");
    
    // Create an array containing hobbies
    Json::JArray hobbies;
    hobbies.append("reading");
    hobbies.append("traveling");

    // Add the hobbies array to the object
    person.set("hobbies", hobbies);

    // Convert Json object to string
    Json::JParser parser(person);
    std::cout << parser.dump(4) << std::endl;
    return 0;
}
```

Running this program, the output result is as follows:

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

Note: Regarding the order of key-value pairs, the JsonBuilder library sorts them by the order of addition in the code by default, **that is, the last added key-value pair will be at the front**.

You can use the following code to perform `generate → parse → regenerate` to make the added key-values in order.

```cpp
Json::JParser parser(person);
std::string json = parser.dump(4);
parser.parse(json);
std::cout << parser.dump(4) << std::endl;
```

## Example 2: Reading a List of Multiple Users' Information

Suppose you need to read all user information from the `users.json` file, you can use the JsonBuilder library to implement it:

Assuming the content of the `users.json` file is as follows:

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
#include <JsonBuilder/Json.h> // Assuming using static/dynamic library

int main() {
    // Parse the file through JParser and specify the maximum length per line as 127 characters
    Json::JParser parser("users.json", 127);
    // Get the parsed JSON array
    Json::JArray users = parser.array();
    // Iterate through the JSON array to get each user's information
    for (size_t i = 0; i < users.size(); i++) {
        auto user = users.toObject(i);
        std::cout << "Name: " << user->toString("name") << std::endl;
        std::cout << "Age: " << user->toInt("age") << std::endl;
        std::cout << "Gender: " << user->toString("gender") << std::endl << std::endl;
    }
    return 0;
}
```

Running this program, the output result is as follows:

```
Name: Alice
Age: 18
Gender: female

Name: Bob
Age: 20
Gender: male
```

## Using JsonBuilder Example Program to Run Examples

Regarding all usage examples provided in the JsonBuilder library, you can view all header file examples through the `examples` directory under the `examples` directory. You can directly test and run the examples through the `JsonBuilderExamples` executable file under the `examples` directory.

# Learn More

- [Class Reference](class.md)
- [Usage Guide](usage.md)
- [Building JsonBuilder with CMake](cmake.md)