#pragma once
#ifndef JSONBUILDERTESTCASE_JARRAY_H
#define JSONBUILDERTESTCASE_JARRAY_H
#include "../../src/Json.h"
#include <cassert>

namespace Test_Array {
    void test1() {
        std::cout << "\nTest 1: Basic Array Operations\n";
        std::cout << "-----------------------------\n";
        
        // Test basic push and access operations
        Json::JArray arr;
        
        // Test pushBack
        arr.pushBack("string");
        arr.pushBack(42);
        arr.pushBack(true);
        arr.pushBack(3.14);
        
        std::cout << "Testing pushBack and size...";
        assert(arr.size() == 4);
        assert(arr.length() == 4); // Test length alias
        std::cout << " ✓\n";
        
        std::cout << "Testing element access...";
        assert(arr.toString(0) == "string");
        assert(arr.toInt(1) == 42);
        assert(arr.toBool(2) == true);
        assert(arr.toDouble(3) == 3.14);
        std::cout << " ✓\n";
        
        // Test get method
        std::cout << "Testing get method...";
        const Json::JValue& val0 = arr.get(0);
        assert(val0.index() == 6); // string type
        assert(std::get<std::string>(val0) == "string");
        std::cout << " ✓\n";
        
        // Test operator<<
        std::cout << "Testing operator<<...";
        arr << std::monostate{} << true << 3.1416926 << 1451986 << "string" << Json::JObject() << Json::JArray();
        assert(arr.size() == 11);
        std::cout << " ✓\n";
        
        // Test clear
        std::cout << "Testing clear...";
        arr.clear();
        assert(arr.size() == 0);
        std::cout << " ✓\n";
        
        std::cout << "All basic array operations passed!\n";
    }

    void test2() {
        std::cout << "\nTest 2: Array Modification Operations\n";
        std::cout << "-----------------------------------\n";
        
        Json::JArray arr;
        
        // Test pushFront
        std::cout << "Testing pushFront...";
        arr.pushFront(3);
        arr.pushFront(2);
        arr.pushFront(1);
        assert(arr.size() == 3);
        assert(arr.toInt(0) == 1);
        assert(arr.toInt(1) == 2);
        assert(arr.toInt(2) == 3);
        std::cout << " ✓\n";
        
        // Test insert
        std::cout << "Testing insert...";
        arr.insert(1, 100);
        assert(arr.size() == 4);
        assert(arr.toInt(0) == 1);
        assert(arr.toInt(1) == 100);
        assert(arr.toInt(2) == 2);
        assert(arr.toInt(3) == 3);
        std::cout << " ✓\n";
        
        // Test popFront
        std::cout << "Testing popFront...";
        arr.popFront();
        assert(arr.size() == 3);
        assert(arr.toInt(0) == 100);
        std::cout << " ✓\n";
        
        // Test popBack
        std::cout << "Testing popBack...";
        arr.popBack();
        assert(arr.size() == 2);
        assert(arr.toInt(1) == 2);
        std::cout << " ✓\n";
        
        // Test remove
        std::cout << "Testing remove...";
        arr.remove(0);
        assert(arr.size() == 1);
        assert(arr.toInt(0) == 2);
        std::cout << " ✓\n";
        
        std::cout << "All array modification operations passed!\n";
    }

    void test3() {
        std::cout << "\nTest 3: Iterators and Sorting\n";
        std::cout << "---------------------------\n";
        
        Json::JArray arr;
        arr.pushBack(5);
        arr.pushBack(1);
        arr.pushBack(3);
        arr.pushBack(4);
        arr.pushBack(2);
        
        // Test iterators
        std::cout << "Testing iterators...";
        size_t count = 0;
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            count++;
        }
        assert(count == 5);
        
        // Test const iterators
        const Json::JArray& const_arr = arr;
        size_t const_count = 0;
        for (auto it = const_arr.begin(); it != const_arr.end(); ++it) {
            const_count++;
        }
        assert(const_count == 5);
        std::cout << " ✓\n";
        
        // Test sorting
        std::cout << "Testing sorting...";
        arr.sort([](Json::JValue& a, Json::JValue& b) {
            return std::get<int32_t>(a) < std::get<int32_t>(b);
        });
        
        assert(arr.toInt(0) == 1);
        assert(arr.toInt(1) == 2);
        assert(arr.toInt(2) == 3);
        assert(arr.toInt(3) == 4);
        assert(arr.toInt(4) == 5);
        std::cout << " ✓\n";
        
        std::cout << "All iterator and sorting tests passed!\n";
    }
    
    void test4() {
        std::cout << "\nTest 4: Error Handling and Edge Cases\n";
        std::cout << "-----------------------------------\n";
        
        Json::JArray arr;
        arr.pushBack("string");
        
        // Test out of bounds access
        std::cout << "Testing out of bounds access...";
        try {
            arr.toInt(10); // Should throw exception
            assert(false);
        } catch (const std::exception& e) {
            std::cout << " ✓\n";
        }
        
        // Test wrong type conversion
        std::cout << "Testing wrong type conversion...";
        try {
            arr.toInt(0); // Should throw GetBadValueException
            assert(false);
        } catch (const Json::JException::GetBadValueException& e) {
            std::cout << " ✓\n";
        }
        
        // Test nested structures
        std::cout << "Testing nested structures...";
        Json::JObject nested_obj;
        nested_obj.set("key", "value");
        arr.pushBack(nested_obj);
        
        Json::JArray nested_arr;
        nested_arr.pushBack(1);
        nested_arr.pushBack(2);
        arr.pushBack(nested_arr);
        
        assert(arr.size() == 3);
        const Json::JObject* obj_ptr = arr.toObject(1);
        assert(obj_ptr != nullptr);
        assert(obj_ptr->toString("key") == "value");
        
        const Json::JArray* arr_ptr = arr.toArray(2);
        assert(arr_ptr != nullptr);
        assert(arr_ptr->size() == 2);
        assert(arr_ptr->toInt(0) == 1);
        std::cout << " ✓\n";
        
        std::cout << "All error handling and edge case tests passed!\n";
    }

    int start() {
        std::cout << "======= JArray Test Case =======\n";
        test1();
        test2();
        test3();
        test4();
        std::cout << "=================================\n";
        return 0;
    }
}

#endif //JSONBUILDERTESTCASE_JARRAY_H
