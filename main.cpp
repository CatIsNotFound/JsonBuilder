#include <iostream>
#include "src/Json.h"

void print_array(const Json::JArray& array) {
    std::cout << "[";
    for (auto& i : array) {
        if (i.index() == Json::JDataType::Bool) {
            std::cout << (get<bool>(i) ? "true" : "false");
        } else if (i.index() == Json::JDataType::Int) {
            std::cout << get<int>(i);
        } else if (i.index() == Json::JDataType::BigInt) {
            std::cout << get<int64_t>(i);
        } else if (i.index() == Json::JDataType::Float) {
            std::cout << get<float>(i);
        } else if (i.index() == Json::JDataType::Double) {
            std::cout << get<double>(i);
        } else if (i.index() == Json::JDataType::String) {
            std::cout << get<std::string>(i);
        } else if (i.index() == Json::JDataType::Array) {
            print_array(*get<std::shared_ptr<Json::JArray>>(i));
        }
        std::cout << " ";
    }
    std::cout << "]";
}

int main() {
    Json::JParser parser;
    parser.parseFromJsonFile("simple.json", 512);
    auto arr = parser.array();
    arr.append("space\tspace");
    parser.setRootArray(arr);
    std::cout << "Json: \n" << parser.dump() << std::endl;
    std::cout << "J1: " << parser.array().toObject(0)->toString("name") << "\n";
    return 0;
}
