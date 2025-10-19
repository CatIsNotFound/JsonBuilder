
#ifndef JSONBUILDER_JSON_H
#define JSONBUILDER_JSON_H
#include <utility>
#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include <variant>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>

namespace Json {
    class KeyIsNotFoundException : public std::exception {
    public:
        explicit KeyIsNotFoundException(std::string msg) : _msg(std::move(msg)) {}
        [[nodiscard]] const char * what() const noexcept override {
            return _msg.c_str();
        }
    private:
        std::string _msg;
    };

    class GetBadValueException : public std::exception {
    public:
        explicit GetBadValueException(std::string msg) : _msg(std::move(msg)) {}
        [[nodiscard]] const char * what() const noexcept override {
            return _msg.c_str();
        }
    private:
        std::string _msg;
    };

    class ParseJsonError : public std::exception {
    public:
        explicit ParseJsonError(std::string msg) : _msg(std::move(msg)) {}
        [[nodiscard]] const char * what() const noexcept override {
            return _msg.c_str();
        }
    private:
        std::string _msg;
    };

    enum JDataType {
        Null,
        Bool,
        Int,
        BigInt,
        Float,
        Double,
        String,
        Array,
        Object
    };

    class JObject;
    class JArray;
    using JValue = std::variant<
        std::monostate,
        bool,
        int32_t,
        int64_t,
        float,
        double,
        std::string,
        std::shared_ptr<JArray>,
        std::shared_ptr<JObject>
    >;
    class JObject {
    public:
        explicit JObject();
        using constIterator = std::unordered_map<std::string, JValue>::const_iterator;
        using iterator = std::unordered_map<std::string, JValue>::iterator;

        [[nodiscard]] constIterator begin() const;
        [[nodiscard]] constIterator end() const;
        [[nodiscard]] iterator begin();
        [[nodiscard]] iterator end();
        [[nodiscard]] size_t size() const;

        void set(const std::string &key, const JValue &value = std::monostate{});
        void set(const std::string &key, const JArray &array);
        void set(const std::string &key, const JObject &object);
        JValue & get(const std::string &key);
        bool valid(const std::string &key);
        void remove(const std::string &key);
        void clear();

        bool toBool(const std::string &key) const;
        int32_t toInt(const std::string &key) const;
        int64_t toBigInt(const std::string &key) const;
        float toFloat(const std::string &key) const;
        double toDouble(const std::string &key) const;
        const std::string & toString(const std::string &key) const;
        const JArray* toArray(const std::string &key) const;
        const JObject* toObject(const std::string &key) const;

        std::vector<std::string> keys() const;
        bool isNull(const std::string &key) const;

        JValue & operator[](const std::string &key);
    private:
        std::unordered_map<std::string, JValue> _dict;
    };

    class JArray {
    public:
        using constIterator = std::vector<JValue>::const_iterator;
        using iterator = std::vector<JValue>::iterator;

        explicit JArray();

        [[nodiscard]] constIterator begin() const;
        [[nodiscard]] constIterator end() const;
        [[nodiscard]] iterator begin();
        [[nodiscard]] iterator end();
        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t length() const;
        [[nodiscard]] const JValue& get(size_t index) const;

        bool toBool(size_t index) const;
        int32_t toInt(size_t index) const;
        int64_t toBigInt(size_t index) const;
        float toFloat(size_t index) const;
        double toDouble(size_t index) const;
        const std::string & toString(size_t index) const;
        const JArray* toArray(size_t index) const;
        const JObject* toObject(size_t index) const;

        void pushBack(const JValue& value);
        void pushBack(const JArray& array);
        void pushBack(const JObject& object);
        void pushFront(const JValue& value);
        void pushFront(const JArray& array);
        void pushFront(const JObject& object);
        void append(const JValue& value);
        void append(const JArray& array);
        void append(const JObject& object);
        void insert(size_t index, const JValue& value);
        void insert(size_t index, const JArray& value);
        void insert(size_t index, const JObject& value);
        void remove(size_t index);
        void popFront();
        void popBack();
        void clear();
        void sort(const std::function<bool(JValue&, JValue&)>& sort_function);

        void operator<<(const JValue& value);
    private:
        std::vector<JValue> _dict;
    };

    class JParser {
    public:
        explicit JParser(JObject root_object);
        explicit JParser(JArray root_array);
        explicit JParser(const std::string &file_name, uint32_t max_cols_inline = 1024);
        explicit JParser();

        void parse(const std::string &json);
        bool parseFromJsonFile(const std::string &file_name, uint32_t max_cols_inline = 1024);
        std::string dump(uint8_t space = 2);
        bool dumpToJsonFile(const std::string& file_name, uint8_t space = 2);
        const JObject & object() const;
        const JArray & array() const;
        void setRootObject(JObject root_object);
        void setRootArray(JArray root_array);
    private:
        struct Token {
            std::string type;
            std::string value;
            size_t line;
            size_t col;
        };
        std::string parseObject(const JObject &object, const std::string &spacer, uint8_t indentation_level);
        std::string parseArray(const Json::JArray *array, const std::string &spacer, uint8_t indentation_level);

        static std::string stripZero(const float& f);
        static std::string stripZero(const double& d);
        static std::vector<Token> extract(const std::string &json, uint32_t &line, uint32_t &col);
        static Token extractString(const std::string &json, size_t &pos, uint32_t &line, uint32_t &col);
        static Token extractNumber(const std::string &json, size_t &pos, uint32_t &line, uint32_t &col);
        static bool hasLastOfType(const std::vector<Token> &tokens, const std::string &type,
                                  const std::string &ends_with_type = "");
        static JObject parseObject(const std::vector<Token>& tokens, size_t& pos);
        static JArray parseArray(const std::vector<Token>& tokens, size_t& pos);
        static JValue parseValue(const Token& token);
        std::string _json;
        JObject _root_object;
        JArray _root_array;
    };

    std::string escToString(const std::string& str);
    std::string strToEscape(const std::string& str);
}

#endif //JSONBUILDER_JSON_H
