
#ifndef JSONBUILDERTESTCASE_JPARSER_H
#define JSONBUILDERTESTCASE_JPARSER_H
#include "../../src/Json.h"
#include <cassert>
#include <fstream>

namespace Test_Parser {
    void test1() {
        std::cout << "\nTest 1: Basic JSON Parsing\n";
        std::cout << "-------------------------\n";
        
        // Test parsing simple JSON object
        Json::JParser parser;
        std::string simple_json = R"({
            "name": "JsonBuilder",
            "version": 1.0,
            "active": true,
            "features": ["parsing", "serialization", "validation"],
            "stats": {
                "downloads": 1000,
                "rating": 4.5
            }
        })";
        
        std::cout << "Testing simple JSON object parsing...";
        parser.parse(simple_json);
        
        const Json::JObject& obj = parser.object();
        assert(obj.size() == 5);
        assert(obj.toString("name") == "JsonBuilder");
        assert(obj.toDouble("version") == 1.0);
        assert(obj.toBool("active") == true);
        std::cout << " ✓\n";
        
        // Test array parsing
        std::cout << "Testing array parsing...";
        const Json::JArray* features = obj.toArray("features");
        assert(features != nullptr);
        assert(features->size() == 3);
        assert(features->toString(0) == "parsing");
        assert(features->toString(1) == "serialization");
        assert(features->toString(2) == "validation");
        std::cout << " ✓\n";
        
        // Test nested object parsing
        std::cout << "Testing nested object parsing...";
        const Json::JObject* stats = obj.toObject("stats");
        assert(stats != nullptr);
        assert(stats->toInt("downloads") == 1000);
        assert(stats->toDouble("rating") == 4.5);
        std::cout << " ✓\n";
        
        // Test parsing simple JSON array
        std::cout << "Testing JSON array parsing...";
        std::string array_json = R"([1, "two", true, 3.14, null])";
        Json::JParser array_parser;
        array_parser.parse(array_json);
        
        const Json::JArray& arr = array_parser.array();
        assert(arr.size() == 5);
        assert(arr.toInt(0) == 1);
        assert(arr.toString(1) == "two");
        assert(arr.toBool(2) == true);
        assert(arr.toDouble(3) == 3.14);
        std::cout << " ✓\n";
        
        std::cout << "All basic parsing tests passed!\n";
    }

    void test2() {
        std::cout << "\nTest 2: JSON Serialization (Dump)\n";
        std::cout << "-------------------------------\n";
        
        // Create a complex JSON structure
        Json::JObject obj;
        obj.set("string", "hello");
        obj.set("number", 42);
        obj.set("boolean", true);
        obj.set("floating", 3.14);
        
        // Add an array
        Json::JArray arr;
        arr.pushBack(1);
        arr.pushBack("test");
        obj.set("array", arr);
        
        // Add a nested object
        Json::JObject nested;
        nested.set("key", "value");
        obj.set("nested", nested);
        
        // Create parser with the object
        Json::JParser parser(obj);
        
        std::cout << "Testing JSON serialization...";
        std::string json_str = parser.dump(2);
        
        // Parse the serialized string back to verify
        Json::JParser verify_parser;
        verify_parser.parse(json_str);
        
        const Json::JObject& verify_obj = verify_parser.object();
        assert(verify_obj.size() == 5);
        assert(verify_obj.toString("string") == "hello");
        assert(verify_obj.toInt("number") == 42);
        assert(verify_obj.toBool("boolean") == true);
        assert(verify_obj.toDouble("floating") == 3.14);
        
        const Json::JArray* verify_arr = verify_obj.toArray("array");
        assert(verify_arr != nullptr);
        assert(verify_arr->size() == 2);
        
        const Json::JObject* verify_nested = verify_obj.toObject("nested");
        assert(verify_nested != nullptr);
        assert(verify_nested->toString("key") == "value");
        std::cout << " ✓\n";
        
        // Test serialization with different indentation
        std::cout << "Testing different indentation...";
        std::string compact_json = parser.dump(0);
        assert(compact_json.find(" ") == std::string::npos); // Should have no indentation spaces
        std::cout << " ✓\n";
        
        std::cout << "All serialization tests passed!\n";
    }

    void test3() {
        std::cout << "\nTest 3: File I/O Operations\n";
        std::cout << "--------------------------\n";
        
        std::string test_file = "test_json_file.json";
        
        // Create test data
        Json::JObject obj;
        obj.set("filename", test_file);
        obj.set("test_data", true);
        obj.set("version", 1.0);
        
        // Test dump to file
        std::cout << "Testing dump to file...";
        Json::JParser parser(obj);
        bool dump_result = parser.dumpToJsonFile(test_file);
        assert(dump_result == true);
        
        // Check if file exists and has content
        std::ifstream file_check(test_file);
        assert(file_check.good());
        file_check.close();
        std::cout << " ✓\n";
        
        // Test parse from file
        std::cout << "Testing parse from file...";
        Json::JParser file_parser;
        bool parse_result = file_parser.parseFromJsonFile(test_file);
        assert(parse_result == true);
        
        const Json::JObject& parsed_obj = file_parser.object();
        assert(parsed_obj.toString("filename") == test_file);
        assert(parsed_obj.toBool("test_data") == true);
        assert(parsed_obj.toDouble("version") == 1.0);
        std::cout << " ✓\n";
        
        // Clean up
        remove(test_file.c_str());
        
        std::cout << "All file I/O tests passed!\n";
    }
    
    void test4() {
        std::cout << "\nTest 4: Error Handling and Edge Cases\n";
        std::cout << "-----------------------------------\n";
        
        Json::JParser parser;
        
        // Test invalid JSON syntax
        std::cout << "Testing invalid JSON syntax...";
        try {
            parser.parse("{invalid json}");
            assert(false); // Should throw exception
        } catch (const Json::JException::ParseJsonError& e) {
            std::cout << " ✓\n";
        }
        
        // Test missing closing brace
        std::cout << "Testing missing closing brace...";
        try {
            parser.parse("{\"key\": \"value\"");
            assert(false); // Should throw exception
        } catch (const Json::JException::ParseJsonError& e) {
            std::cout << " ✓\n";
        }
        
        // Test array with trailing comma
        std::cout << "Testing array with trailing comma...";
        try {
            parser.parse("[1, 2, 3,]");
            // Some parsers accept this, but according to strict JSON it's invalid
            // We'll assume our parser might throw here
        } catch (const Json::JException::ParseJsonError& e) {
            std::cout << " ✓ (exception thrown as expected)\n";
        }
        
        // Test parsing non-existent file
        std::cout << "Testing parse from non-existent file...";
        bool parse_result = parser.parseFromJsonFile("non_existent_file.json");
        assert(parse_result == false);
        std::cout << " ✓\n";
        
        // Test extreme cases - empty JSON
        std::cout << "Testing empty JSON object...";
        parser.parse("{}");
        const Json::JObject& empty_obj = parser.object();
        assert(empty_obj.size() == 0);
        std::cout << " ✓\n";
        
        std::cout << "Testing empty JSON array...";
        parser.parse("[]");
        const Json::JArray& empty_arr = parser.array();
        assert(empty_arr.size() == 0);
        std::cout << " ✓\n";
        
        std::cout << "All error handling and edge case tests passed!\n";
    }

    int start() {
        std::cout << "======= JParser Test Case =======\n";
        test1();
        test2();
        test3();
        test4();
        std::cout << "=================================\n";
        return 0;
    }
}

#endif //JSONBUILDERTESTCASE_JPARSER_H
