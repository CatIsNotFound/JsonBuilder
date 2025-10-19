#pragma once
#ifndef JSONBUILDER_JPERFORMANCETEST_H
#define JSONBUILDER_JPERFORMANCETEST_H
#include "../../src/Json.h"
#include <cassert>
#include <chrono>
#include <string>
#include <iostream>

namespace Test_Performance {
    void test1() {
        std::cout << "\nTest 1: Basic Operations\n" << std::flush;
        std::cout << "------------------------\n" << std::flush;
        
        // Simple object test
        std::cout << "Object test..." << std::flush;
        Json::JObject obj;
        obj.set("key1", 123);
        obj.set("key2", "test");
        assert(obj.size() == 2);
        std::cout << " OK\n" << std::flush;
        
        // Simple array test
        std::cout << "Array test..." << std::flush;
        Json::JArray arr;
        arr.pushBack(1);
        arr.pushBack(2);
        arr.pushBack(3);
        assert(arr.size() == 3);
        std::cout << " OK\n" << std::flush;
    }
    
    void test2() {
        std::cout << "\nTest 2: Simple Parsing\n" << std::flush;
        std::cout << "---------------------\n" << std::flush;
        
        // Very simple JSON parsing
        std::string json = "{\"name\":\"test\",\"value\":123}";
        std::cout << "Parsing JSON..." << std::flush;
        Json::JParser parser;
        parser.parse(json);
        assert(parser.object().toString("name") == "test");
        std::cout << " OK\n" << std::flush;
    }
    
    void test3() {
        std::cout << "\nTest 3: Nested Structure\n" << std::flush;
        std::cout << "------------------------\n" << std::flush;
        
        // Simple nested object
        std::cout << "Nested object test..." << std::flush;
        Json::JObject root;
        Json::JObject child;
        child.set("x", 100);
        root.set("child", child);
        assert(root.toObject("child")->toInt("x") == 100);
        std::cout << " OK\n" << std::flush;
    }
    
    void test4() {
        std::cout << "\nTest 4: Error Test\n" << std::flush;
        std::cout << "------------------\n" << std::flush;
        
        // Basic error handling
        std::cout << "Error handling test..." << std::flush;
        try {
            Json::JParser parser;
            parser.parse("{invalid}");
        } catch (const Json::JException::ParseJsonError& e) {
            std::cout << " OK\n" << std::flush;
            return;
        }
        assert(false); // Should have thrown exception
    }

    int start() {
        std::cout << "\nPerformance Tests Started\n" << std::flush;
        test1();
        test2();
        test3();
        test4();
        std::cout << "\nAll Performance Tests Completed\n" << std::flush;
        return 0;
    }
}

#endif //JSONBUILDER_JPERFORMANCETEST_H