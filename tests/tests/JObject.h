#pragma once
#ifndef JSONBUILDERTESTCASE_JOBJECT_H
#define JSONBUILDERTESTCASE_JOBJECT_H
#include "../../src/Json.h"
#include <cassert>

namespace Test_Object {
    void test1() {
        std::cout << "\nTest 1: Basic Object Operations\n";
        std::cout << "------------------------------\n";
        
        // Test basic set and get operations
        Json::JObject obj;
        
        // Set various types of values
        obj.set("string_key", "string_value");
        obj.set("int_key", 42);
        obj.set("bool_key", true);
        obj.set("double_key", 3.14159);
        
        std::cout << "Testing set and get operations...";
        assert(obj.size() == 4);
        assert(obj.valid("string_key"));
        assert(obj.valid("int_key"));
        assert(obj.valid("bool_key"));
        assert(obj.valid("double_key"));
        
        // Test type conversion methods
        assert(obj.toString("string_key") == "string_value");
        assert(obj.toInt("int_key") == 42);
        assert(obj.toBool("bool_key") == true);
        assert(obj.toDouble("double_key") == 3.14159);
        std::cout << " ✓\n";
        
        // Test operator[] access
        std::cout << "Testing operator[] access...";
        Json::JValue& string_val = obj["string_key"];
        assert(std::get<std::string>(string_val) == "string_value");
        
        // Test remove operation
        obj.remove("int_key");
        assert(obj.size() == 3);
        assert(!obj.valid("int_key"));
        std::cout << " ✓\n";
        
        // Test clear operation
        obj.clear();
        std::cout << "Testing clear operation...";
        assert(obj.size() == 0);
        assert(!obj.valid("string_key"));
        std::cout << " ✓\n";
        
        std::cout << "All basic object operations passed!\n";
    }

    void test2() {
        std::cout << "\nTest 2: Error Handling and Exception\n";
        std::cout << "----------------------------------\n";
        
        Json::JObject obj;
        obj.set("string_key", "string_value");
        obj.set("int_key", 42);
        
        // Test invalid key access
        std::cout << "Testing invalid key access...";
        try {
            obj.toInt("non_existent_key");
            assert(false); // Should throw exception
        } catch (const Json::JException::KeyIsNotFoundException& e) {
            std::cout << " ✓\n";
        } catch (...) {
            assert(false); // Wrong exception type
        }
        
        // Test wrong type conversion
        std::cout << "Testing wrong type conversion...";
        try {
            obj.toInt("string_key"); // This should throw GetBadValueException
            assert(false); // Should throw exception
        } catch (const Json::JException::GetBadValueException& e) {
            std::cout << " ✓\n";
        } catch (...) {
            assert(false); // Wrong exception type
        }
        
        // Test null values
        std::cout << "Testing null values...";
        obj.set("null_key"); // Set to default null value
        assert(obj.valid("null_key"));
        assert(obj.isNull("null_key"));
        try {
            obj.toString("null_key"); // This should throw GetBadValueException
            assert(false); // Should throw exception
        } catch (const Json::JException::GetBadValueException& e) {
            std::cout << " ✓\n";
        }
        
        std::cout << "All error handling tests passed!\n";
    }

    void test3() {
        std::cout << "\nTest 3: Iterators and Keys\n";
        std::cout << "------------------------\n";
        
        Json::JObject obj;
        obj.set("key1", "value1");
        obj.set("key2", 2);
        obj.set("key3", true);
        
        // Test keys() method
        std::cout << "Testing keys() method...";
        std::vector<std::string> keys = obj.keys();
        assert(keys.size() == 3);
        
        // Check that all keys are present (order may vary due to unordered_map)
        bool has_key1 = false, has_key2 = false, has_key3 = false;
        for (const auto& key : keys) {
            if (key == "key1") has_key1 = true;
            else if (key == "key2") has_key2 = true;
            else if (key == "key3") has_key3 = true;
        }
        assert(has_key1 && has_key2 && has_key3);
        std::cout << " ✓\n";
        
        // Test iterators
        std::cout << "Testing iterators...";
        size_t count = 0;
        for (const auto& [key, value] : obj) {
            count++;
            assert(obj.valid(key)); // All keys from iterator should be valid
        }
        assert(count == 3);
        std::cout << " ✓\n";
        
        // Test const iterator
        size_t const_count = 0;
        const Json::JObject& const_obj = obj;
        for (auto it = const_obj.begin(); it != const_obj.end(); ++it) {
            const_count++;
        }
        assert(const_count == 3);
        std::cout << " ✓\n";
        
        std::cout << "All iterator and keys tests passed!\n";
    }
    
    void test4() {
        std::cout << "\nTest 4: Nested Objects and Complex Structures\n";
        std::cout << "------------------------------------------\n";
        
        // Test nested objects
        Json::JObject outer;
        Json::JObject inner;
        inner.set("inner_key", "inner_value");
        outer.set("inner_object", inner);
        
        // Test nested arrays
        Json::JArray arr;
        arr.pushBack(1);
        arr.pushBack(2);
        outer.set("array", arr);
        
        std::cout << "Testing nested object access...";
        assert(outer.valid("inner_object"));
        const Json::JObject* inner_ptr = outer.toObject("inner_object");
        assert(inner_ptr != nullptr);
        assert(inner_ptr->toString("inner_key") == "inner_value");
        std::cout << " ✓\n";
        
        std::cout << "Testing nested array access...";
        assert(outer.valid("array"));
        const Json::JArray* arr_ptr = outer.toArray("array");
        assert(arr_ptr != nullptr);
        assert(arr_ptr->size() == 2);
        assert(arr_ptr->toInt(0) == 1);
        assert(arr_ptr->toInt(1) == 2);
        std::cout << " ✓\n";
        
        std::cout << "All nested structure tests passed!\n";
    }

    int start() {
        std::cout << "======= JObject Test Case =======\n";
        test1();
        test2();
        test3();
        test4();
        std::cout << "=================================\n";
        return 0;
    }
}

#endif //JSONBUILDERTESTCASE_JOBJECT_H
