
#pragma once
#ifndef JSONBUILDER_JDATATYPE_H
#define JSONBUILDER_JDATATYPE_H
#include "../../src/Json.h"
#include <cassert>

namespace Test_DataType {
    void test1() {
        std::cout << "\nTest 1: Basic JValue Types\n";
        std::cout << "------------------------\n";
        
        // Test basic data types
        Json::JValue null_val = std::monostate{};
        Json::JValue bool_val = true;
        Json::JValue int_val = int32_t(42);
        Json::JValue bigint_val = int64_t(9223372036854775807LL); // Max int64
        Json::JValue float_val = 3.14f;
        Json::JValue double_val = 3.1415926535;
        Json::JValue string_val = std::string("Hello, World!");
        
        // Test variant index matches expected types
        std::cout << "Testing null value type...";
        assert(null_val.index() == 0); // std::monostate
        std::cout << " ✓\n";
        
        std::cout << "Testing bool value type...";
        assert(bool_val.index() == 1); // bool
        assert(std::get<bool>(bool_val) == true);
        std::cout << " ✓\n";
        
        std::cout << "Testing int value type...";
        assert(int_val.index() == 2); // int32_t
        assert(std::get<int32_t>(int_val) == 42);
        std::cout << " ✓\n";
        
        std::cout << "Testing bigint value type...";
        assert(bigint_val.index() == 3); // int64_t
        assert(std::get<int64_t>(bigint_val) == 9223372036854775807LL);
        std::cout << " ✓\n";
        
        std::cout << "Testing float value type...";
        assert(float_val.index() == 4); // float
        assert(std::get<float>(float_val) == 3.14f);
        std::cout << " ✓\n";
        
        std::cout << "Testing double value type...";
        assert(double_val.index() == 5); // double
        assert(std::get<double>(double_val) == 3.1415926535);
        std::cout << " ✓\n";
        
        std::cout << "Testing string value type...";
        assert(string_val.index() == 6); // std::string
        assert(std::get<std::string>(string_val) == "Hello, World!");
        std::cout << " ✓\n";
        
        std::cout << "All basic data type tests passed!\n";
    }

    void test2() {
        std::cout << "\nTest 2: Edge Cases and Boundary Values\n";
        std::cout << "------------------------------------\n";
        
        // Test boundary values
        Json::JValue min_int = int32_t(-2147483648); // Min int32
        Json::JValue max_int = int32_t(2147483647);  // Max int32
        Json::JValue min_bigint = int64_t(-9223372036854775808LL); // Min int64
        Json::JValue max_bigint = int64_t(9223372036854775807LL);  // Max int64
        Json::JValue zero = int32_t(0);
        Json::JValue negative = int32_t(-1);
        Json::JValue empty_string = std::string("");
        Json::JValue special_chars = std::string("!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/");
        
        std::cout << "Testing int32 boundaries...";
        assert(std::get<int32_t>(min_int) == -2147483648);
        assert(std::get<int32_t>(max_int) == 2147483647);
        std::cout << " ✓\n";
        
        std::cout << "Testing int64 boundaries...";
        assert(std::get<int64_t>(min_bigint) == -9223372036854775808LL);
        assert(std::get<int64_t>(max_bigint) == 9223372036854775807LL);
        std::cout << " ✓\n";
        
        std::cout << "Testing zero and negative values...";
        assert(std::get<int32_t>(zero) == 0);
        assert(std::get<int32_t>(negative) == -1);
        std::cout << " ✓\n";
        
        std::cout << "Testing string edge cases...";
        assert(std::get<std::string>(empty_string).empty());
        assert(std::get<std::string>(special_chars) == "!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/");
        std::cout << " ✓\n";
        
        std::cout << "All boundary value tests passed!\n";
    }

    void test3() {
        std::cout << "\nTest 3: Container Types (Object and Array)\n";
        std::cout << "----------------------------------------\n";
        
        // Test object creation and basic operations
        Json::JObject obj;
        obj.set("name", "JsonBuilder");
        obj.set("version", 1.0);
        obj.set("active", true);
        
        // Test array creation and basic operations
        Json::JArray arr;
        arr.pushBack(1);
        arr.pushBack("test");
        arr.pushBack(false);
        
        // Test embedding objects and arrays
        Json::JObject nested_obj;
        nested_obj.set("nested", "value");
        obj.set("metadata", nested_obj);
        
        Json::JArray nested_arr;
        nested_arr.pushBack(1);
        nested_arr.pushBack(2);
        arr.pushBack(nested_arr);
        
        std::cout << "Testing object creation and properties...";
        assert(obj.size() == 4);
        assert(obj.valid("name"));
        assert(obj.toString("name") == "JsonBuilder");
        assert(obj.toDouble("version") == 1.0);
        assert(obj.toBool("active") == true);
        std::cout << " ✓\n";
        
        std::cout << "Testing array creation and elements...";
        assert(arr.size() == 4);
        assert(arr.toInt(0) == 1);
        assert(arr.toString(1) == "test");
        assert(arr.toBool(2) == false);
        std::cout << " ✓\n";
        
        std::cout << "Testing nested structures...";
        assert(obj.valid("metadata"));
        const Json::JObject* meta = obj.toObject("metadata");
        assert(meta != nullptr);
        assert(meta->toString("nested") == "value");
        
        const Json::JArray* nested = arr.toArray(3);
        assert(nested != nullptr);
        assert(nested->size() == 2);
        assert(nested->toInt(0) == 1);
        assert(nested->toInt(1) == 2);
        std::cout << " ✓\n";
        
        std::cout << "All container type tests passed!\n";
    }

    int start() {
        std::cout << "======= JDataType Test Case =======\n";
        test1();
        test2();
        test3();
        std::cout << "===================================\n";
        return 0;
    }
}
#endif //JSONBUILDER_JDATATYPE_H
