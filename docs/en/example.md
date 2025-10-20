# JsonBuilder Usage Examples

## Example 1: Personal Information

The following example creates a JSON object containing personal information:

```cpp
#include <JsonBuilder/Json.h> // Assuming static/dynamic library usage

int main() {
    // Create a JSON object for storing personal information
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

    // Convert the Json object to a string
    Json::JParser parser(person);
    std::cout << parser.dump(4) << std::endl;
    return 0;
}
```

Running this program produces the following output:

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

Note: Regarding the order of key-value pairs, the JsonBuilder library defaults to sorting them based on the order they were added in the code, **with the last added key-value pair appearing first**.

You can achieve a more natural ordering by using a `generate → parse → generate again` approach:

```cpp
Json::JParser parser(person);
std::string json = parser.dump(4);
parser.parse(json);
std::cout << parser.dump(4) << std::endl;
```

## Example 2: Reading a List of Multiple Users

Suppose you need to read all user information from a `users.json` file. You can use the JsonBuilder library to accomplish this:

Assume the `users.json` file contains:

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
#include <JsonBuilder/Json.h> // Assuming static/dynamic library usage

int main() {
    // Parse the file through JParser, specifying a maximum line length of 127 characters
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

Running this program produces the following output:

```
Name: Alice
Age: 18
Gender: female

Name: Bob
Age: 20
Gender: male
```

## Running Examples Using the JsonBuilder Example Program

For all usage examples provided in the JsonBuilder library, you can view examples for all header files in the `examples` directory under the `examples` directory. You can directly run the examples by using the `JsonBuilderExamples` executable file in the `examples` directory.

# Learn More

- [Class Reference](class.md)
- [Usage](usage.md)
- [Building JsonBuilder with CMake](cmake.md)