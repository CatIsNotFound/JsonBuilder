#include "tests/JDataType.h"
#include "tests/JArray.h"
#include "tests/JObject.h"
#include "tests/JParser.h"
#include "tests/JPerformanceTest.h"

void showAvaliableTestCases() {
    std::cout << "All available test case: \n";
    std::cout << "- datatype\n";
    std::cout << "- object\n";
    std::cout << "- array\n";
    std::cout << "- parser\n";
    std::cout << "- performance\n";
}

void showHelp(const char* arg) {
    std::cout << "Usage: " << arg << " [OPTIONS]\n";
    std::cout << "-t, --test-case [VALUE]    Select test case\n";
    std::cout << "-h, --help                 Display help information\n";
    std::cout << "-v, --version              Display version info\n";
}

void showVersion() {
    std::cout << "JsonBuilder Test case v1.0.0\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showHelp(argv[0]);
        return 1;
    }
    std::string option = argv[1];
    if (option == "-t" || option == "--test-case") {
        if (argc < 3) {
            showAvaliableTestCases();
            return 1;
        }
        std::string test_case = argv[2];
        if (test_case == "datatype") {
            return Test_DataType::start();
        } else if (test_case == "object") {
            return Test_Object::start();
        } else if (test_case == "array") {
            return Test_Array::start();
        } else if (test_case == "parser") {
            return Test_Parser::start();
        } else if (test_case == "performance") {
            return Test_Performance::start();
        } else {
            std::cout << "Error: Test case '" << test_case << "' is not found! \n";
            showAvaliableTestCases();
            return 1;
        }
    } else if (option == "-h" || option == "--help") {
        showHelp(argv[0]);
        return 0;
    } else if (option == "-v" || option == "--version") {
        showVersion();
        return 0;
    }
    return 0;
}
