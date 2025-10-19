#include "Json.h"

Json::JObject::JObject() = default;

Json::JObject::constIterator Json::JObject::begin() const {
    return _dict.begin();
}

Json::JObject::constIterator Json::JObject::end() const {
    return _dict.end();
}

Json::JObject::iterator Json::JObject::begin() {
    return _dict.begin();
}

Json::JObject::iterator Json::JObject::end() {
    return _dict.end();
}

size_t Json::JObject::size() const {
    return _dict.size();
}

void Json::JObject::set(const std::string &key, const Json::JValue &value) {
    if (_dict.empty()) {
        _dict.emplace(key, value);
        return;
    }
    if (_dict.contains(key)) {
        _dict[key] = value;
    } else {
        _dict.emplace(key, value);
    }
}

void Json::JObject::set(const std::string &key, const Json::JArray &array) {
    if (_dict.empty()) {
        _dict.emplace(key, std::make_shared<JArray>(array));
        return;
    }
    if (_dict.contains(key)) {
        _dict[key] = std::make_shared<JArray>(array);
    } else {
        _dict.emplace(key, std::make_shared<JArray>(array));
    }
}

void Json::JObject::set(const std::string &key, const Json::JObject &object) {
    if (_dict.empty()) {
        _dict.emplace(key, std::make_shared<JObject>(object));
        return;
    }
    if (_dict.contains(key)) {
        _dict[key] = std::make_shared<JObject>(object);
    } else {
        _dict.emplace(key, std::make_shared<JObject>(object));
    }
}


Json::JValue & Json::JObject::get(const std::string &key) {
    auto ptr = _dict.find(key);
    if (ptr != _dict.end()) {
        return ptr->second;
    }
    throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
}

bool Json::JObject::valid(const std::string &key) {
    return _dict.contains(key);
}

void Json::JObject::remove(const std::string &key) {
    if (_dict.contains(key)) {
        _dict.erase(key);
    }
}

void Json::JObject::clear() {
    _dict.clear();
}

bool Json::JObject::toBool(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<bool>(_dict.at(key)))
        return std::get<bool>(_dict.at(key));
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

int32_t Json::JObject::toInt(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<int32_t>(_dict.at(key)))
        return std::get<int32_t>(_dict.at(key));
    else if (std::holds_alternative<int64_t>(_dict.at(key)))
        return static_cast<int32_t>(std::get<int64_t>(_dict.at(key)));
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

int64_t Json::JObject::toBigInt(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<int64_t>(_dict.at(key)))
        return std::get<int64_t>(_dict.at(key));
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

float Json::JObject::toFloat(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<float>(_dict.at(key)))
        return std::get<float>(_dict.at(key));
    else if (std::holds_alternative<double>(_dict.at(key)))
        return static_cast<float>(std::get<double>(_dict.at(key)));
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

double Json::JObject::toDouble(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<double>(_dict.at(key)))
        return std::get<double>(_dict.at(key));
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

const std::string & Json::JObject::toString(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<std::string>(_dict.at(key)))
        return std::get<std::string>(_dict.at(key));
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

const Json::JArray* Json::JObject::toArray(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<std::shared_ptr<JArray>>(_dict.at(key)))
        return std::get<std::shared_ptr<JArray>>(_dict.at(key)).get();
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

const Json::JObject* Json::JObject::toObject(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    if (std::holds_alternative<std::shared_ptr<JObject>>(_dict.at(key)))
        return std::get<std::shared_ptr<JObject>>(_dict.at(key)).get();
    else
        throw JException::GetBadValueException("Can't get value from key '" + key + "'!");
}

Json::JValue &Json::JObject::operator[](const std::string &key) {
    auto ptr = _dict.find(key);
    if (ptr != _dict.end()) {
        return ptr->second;
    } else {
        /// 默认创建并设定为空值
        _dict.emplace(key, std::monostate{});
        return _dict[key];
    }
}

std::vector<std::string> Json::JObject::keys() const {
    std::vector<std::string> _keys;
    for (auto& k : _dict) {
        _keys.emplace_back(k.first);
    }
    return _keys;
}

bool Json::JObject::isNull(const std::string &key) const {
    if (!_dict.contains(key)) {
        throw JException::KeyIsNotFoundException("The key '" + key + "' is not found in object!");
    }
    return _dict.at(key).index() == JDataType::Null;
}


Json::JArray::JArray() = default;

Json::JArray::constIterator Json::JArray::begin() const {
    return _dict.begin();
}

Json::JArray::constIterator Json::JArray::end() const {
    return _dict.end();
}

Json::JArray::iterator Json::JArray::begin() {
    return _dict.begin();
}

Json::JArray::iterator Json::JArray::end() {
    return _dict.end();
}

size_t Json::JArray::size() const {
    return _dict.size();
}

size_t Json::JArray::length() const {
    return _dict.size();
}

const Json::JValue &Json::JArray::get(size_t index) const {
    return _dict.at(index);
}

bool Json::JArray::toBool(size_t index) const {
    if (std::holds_alternative<bool>(_dict.at(index)))
        return std::get<bool>(_dict.at(index));
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

int32_t Json::JArray::toInt(size_t index) const {
    if (std::holds_alternative<int32_t>(_dict.at(index)))
        return std::get<int32_t>(_dict.at(index));
    else if (std::holds_alternative<int64_t>(_dict.at(index)))
        return static_cast<int32_t>(std::get<int64_t>(_dict.at(index)));
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

int64_t Json::JArray::toBigInt(size_t index) const {
    if (std::holds_alternative<int32_t>(_dict.at(index)))
        return std::get<int32_t>(_dict.at(index));
    else if (std::holds_alternative<int64_t>(_dict.at(index)))
        return std::get<int64_t>(_dict.at(index));
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

float Json::JArray::toFloat(size_t index) const {
    if (std::holds_alternative<float>(_dict.at(index)))
        return std::get<float>(_dict.at(index));
    else if (std::holds_alternative<double>(_dict.at(index)))
        return static_cast<float>(std::get<double>(_dict.at(index)));
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

double Json::JArray::toDouble(size_t index) const {
    if (std::holds_alternative<float>(_dict.at(index)))
        return static_cast<double>(std::get<float>(_dict.at(index)));
    else if (std::holds_alternative<double>(_dict.at(index)))
        return std::get<double>(_dict.at(index));
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

const std::string &Json::JArray::toString(size_t index) const {
    if (std::holds_alternative<std::string>(_dict.at(index)))
        return std::get<std::string>(_dict.at(index));
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

const Json::JArray *Json::JArray::toArray(size_t index) const {
    if (std::holds_alternative<std::shared_ptr<JArray>>(_dict.at(index)))
        return std::get<std::shared_ptr<JArray>>(_dict.at(index)).get();
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

const Json::JObject *Json::JArray::toObject(size_t index) const {
    if (std::holds_alternative<std::shared_ptr<JObject>>(_dict.at(index)))
        return std::get<std::shared_ptr<JObject>>(_dict.at(index)).get();
    else
        throw JException::GetBadValueException("Can't get value from index '" + std::to_string(index) + "'!");
}

void Json::JArray::pushBack(const Json::JValue &value) {
    _dict.push_back(value);
}

void Json::JArray::pushBack(const Json::JArray &array) {
    _dict.push_back(std::make_shared<JArray>(array));
}

void Json::JArray::pushBack(const Json::JObject &object) {
    _dict.push_back(std::make_shared<JObject>(object));
}

void Json::JArray::pushFront(const Json::JValue &value) {
    _dict.insert(_dict.begin(), value);
}

void Json::JArray::pushFront(const Json::JArray &array) {
    _dict.insert(_dict.begin(), std::make_shared<JArray>(array));
}

void Json::JArray::pushFront(const Json::JObject &object) {
    _dict.insert(_dict.begin(), std::make_shared<JObject>(object));
}

void Json::JArray::append(const Json::JValue &value) {
    _dict.push_back(value);
}

void Json::JArray::append(const Json::JArray &array) {
    _dict.emplace_back(std::make_shared<JArray>(array));
}

void Json::JArray::append(const Json::JObject &object) {
    _dict.emplace_back(std::make_shared<JObject>(object));
}

void Json::JArray::insert(size_t index, const Json::JValue &value) {
    _dict.insert(_dict.begin() + index, value);
}

void Json::JArray::insert(size_t index, const Json::JArray &value) {
    _dict.insert(_dict.begin() + index, std::make_shared<JArray>(value));
}

void Json::JArray::insert(size_t index, const Json::JObject &value) {
    _dict.insert(_dict.begin() + index, std::make_shared<JObject>(value));
}

void Json::JArray::remove(size_t index) {
    _dict.erase(_dict.begin() + index);
}

void Json::JArray::popFront() {
    _dict.erase(_dict.begin());
}

void Json::JArray::popBack() {
    _dict.pop_back();
}

void Json::JArray::clear() {
    _dict.clear();
}

void Json::JArray::sort(const std::function<bool(JValue&, JValue&)> &sort_function) {
    if (sort_function) {
        std::sort(_dict.begin(), _dict.end(), sort_function);
    }
}

Json::JArray& Json::JArray::operator<<(const Json::JValue &value) {
    _dict.push_back(value);
    return *this;
}

Json::JArray& Json::JArray::operator<<(const Json::JArray &array) {
    _dict.emplace_back(std::make_shared<JArray>(array));
    return *this;
}

Json::JArray& Json::JArray::operator<<(const Json::JObject &object) {
    _dict.emplace_back(std::make_shared<JObject>(object));
    return *this;
}

Json::JValue& Json::JArray::operator[](size_t index) {
    return _dict.at(index);
}

Json::JParser::JParser(Json::JObject root_object)
    : _root_object(std::move(root_object)) {}

Json::JParser::JParser(Json::JArray root_array)
    : _root_array(std::move(root_array)) {}

Json::JParser::JParser(const std::string &file_name, uint32_t max_cols_inline) {
    std::ifstream file(file_name, std::ios::in);
    std::string json;
    if (!file.is_open()) return;
    char *buf = (char*) calloc(max_cols_inline, sizeof(char));
    while (true) {
        file.getline(buf, max_cols_inline);
        json += buf;
        if (!file.eof()) json += "\n"; else break;
    }
    free(buf);
    file.close();
    parse(json);
}

Json::JParser::JParser() = default;

void Json::JParser::parse(const std::string &json) {
    uint32_t line = 1, col = 1;
    if (json.empty()) return;
    std::vector<Token> tokens = extract(json, line, col);
    size_t pos = 0;
    if (tokens.front().type == "{")
        _root_object = parseObject(tokens, pos);
    else
        _root_array = parseArray(tokens, pos);
}

bool Json::JParser::parseFromJsonFile(const std::string &file_name, uint32_t max_cols_inline) {
    std::ifstream file(file_name, std::ios::in);
    std::string json;
    if (!file.is_open()) return false;
    char *buf = (char*) calloc(max_cols_inline, sizeof(char));
    while (true) {
        file.getline(buf, max_cols_inline);
        json += buf;
        if (!file.eof()) json += "\n"; else break;
    }
    free(buf);
    file.close();
    parse(json);
    return true;
}

std::string Json::JParser::dump(uint8_t space) {
    std::string output;
    std::string spacer;
    for (int i = 0; i < space; ++i) {
        spacer += " ";
    }
    if (_root_object.size())
        output = parseObject(_root_object, spacer, 0);
    else if (_root_array.size())
        output = parseArray(&_root_array, spacer, 0);
    else
        throw std::runtime_error("You have not select object or array to generate json context!");
    return output;
}

bool Json::JParser::dumpToJsonFile(const std::string &file_name, uint8_t space) {
    std::ofstream file(file_name, std::ios::out);
    if (!file.is_open()) return false;
    std::string json = dump(space);
    file << json;
    file.close();
    return true;
}

std::string
Json::JParser::parseObject(const JObject &object, const std::string &spacer, uint8_t indentation_level) {
    std::string output;
    size_t _idx = 0, _size = object.size();
    output += "{";
    if (!_size) {
        output += "}";
        return output;
    }
    output += "\n";
    for (auto& _r : object) {
        for (int i = 0; i < indentation_level + 1; ++i)
            output += spacer;
        output += "\"" + _r.first + "\": ";
        if (_r.second.index() == JDataType::Null) {
            output += "null";
        } else if (_r.second.index() == JDataType::Bool) {
            output += (std::get<bool>(_r.second) ? "true" : "false");
        } else if (_r.second.index() == JDataType::Int) {
            output += std::to_string(std::get<int32_t>(_r.second));
        } else if (_r.second.index() == JDataType::BigInt) {
            output += std::to_string(std::get<int64_t>(_r.second));
        } else if (_r.second.index() == JDataType::Float) {
            output += stripZero(std::get<float>(_r.second));
        } else if (_r.second.index() == JDataType::Double) {
            output += stripZero(std::get<double>(_r.second));
        } else if (_r.second.index() == JDataType::String) {
            auto s = escToString(std::get<std::string>(_r.second));
            output += "\"" + s + "\"";
        } else if (_r.second.index() == JDataType::Array) {
            output += parseArray(std::get<std::shared_ptr<JArray>>(_r.second).get(), spacer, indentation_level + 1);
        } else if (_r.second.index() == JDataType::Object) {
            output += parseObject(*std::get<std::shared_ptr<JObject>>(_r.second), spacer, indentation_level + 1);
        }
        if (++_idx < _size) {
            output += ", \n";
        }
    }
    output += "\n";
    for (int i = 0; i < indentation_level; ++i)
        output += spacer;
    output += "}";
    return output;
}

std::string Json::JParser::parseArray(const Json::JArray *array, const std::string &spacer,
                                      uint8_t indentation_level) {
    std::string array_text;
    array_text += "[";
    size_t _idx = 0;
    size_t _size = array->size();
    if (!_size) {
        array_text += "]";
        return array_text;
    }
    array_text += "\n";
    for (auto& i : *array) {
        for (int j = 0; j < indentation_level + 1; ++j)
            array_text += spacer;
        if (i.index() == Json::JDataType::Null) {
            array_text += "null";
        } else if (i.index() == Json::JDataType::Bool) {
            array_text += (std::get<bool>(i) ? "true" : "false");
        } else if (i.index() == Json::JDataType::Int) {
            array_text += std::to_string(std::get<int>(i));
        } else if (i.index() == Json::JDataType::BigInt) {
            array_text += std::to_string(std::get<int64_t>(i));
        } else if (i.index() == Json::JDataType::Float) {
            array_text += stripZero(std::get<float>(i));
        } else if (i.index() == Json::JDataType::Double) {
            array_text += stripZero(std::get<double>(i));
        } else if (i.index() == Json::JDataType::String) {
            auto s = escToString(std::get<std::string>(i));
            array_text += "\"" + s + "\"";
        } else if (i.index() == Json::JDataType::Array) {
            array_text += parseArray(std::get<std::shared_ptr<JArray>>(i).get(), spacer, indentation_level + 1);
        } else if (i.index() == Json::JDataType::Object) {
            array_text += parseObject(*std::get<std::shared_ptr<JObject>>(i), spacer, indentation_level + 1);
        }
        if (++_idx < _size) {
            array_text += ", \n";
        } else {
            array_text += "\n";
        }
    }
    for (int j = 0; j < indentation_level; ++j)
        array_text += spacer;
    array_text += "]";
    return array_text;
}

std::string Json::JParser::stripZero(const float &f) {
    auto s = std::to_string(f);
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s.back() == '.') s.pop_back();
    return s;
}

std::string Json::JParser::stripZero(const double &d) {
    auto s = std::to_string(d);
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s.back() == '.') s.pop_back();
    return s;
}

const Json::JObject & Json::JParser::object() const {
    return _root_object;
}

const Json::JArray & Json::JParser::array() const {
    return _root_array;
}

void Json::JParser::setRootObject(Json::JObject root_object) {
    _root_object = std::move(root_object);
    _root_array.clear();
}

void Json::JParser::setRootArray(Json::JArray root_array) {
    _root_array = std::move(root_array);
    _root_object.clear();
}

std::vector<Json::JParser::Token> Json::JParser::extract(const std::string &json, uint32_t &line, uint32_t &col) {
    std::vector<Token> tokens;
    bool check_begin = true;
    uint32_t enclosed_1 = 0, enclosed_2 = 0;
    size_t end_pos = 0;
    bool flag_end_pos = false;
    Token temp_token_1, temp_token_2;
    for (size_t i = 0; i < json.size();) {
        char c = json[i];
        if (c == ' ') {
            col++; i++;
        } else if (c == '\n' || c == '\t') {
            line++; col = 1; i++;
        } else if (c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ':') {
            tokens.emplace_back(std::string(1, c), "", line, col);
            if (c == '{') enclosed_1++;
            if (c == '}') {
                enclosed_1--;
                if (!enclosed_1 && !flag_end_pos && tokens.front().type == "{") {
                    end_pos = tokens.size() - 1;
                    flag_end_pos = true;
                }
            }
            if (c == '[') enclosed_2++;
            if (c == ']') {
                enclosed_2--;
                if (!enclosed_2 && !flag_end_pos && tokens.front().type == "[") {
                    end_pos = tokens.size() - 1;
                    flag_end_pos = true;
                }
            }
            i++; col++;
        } else if (c == '"') {
            tokens.emplace_back(extractString(json, i, line, col));
        } else if (isdigit(c) || c == '-') {
            tokens.emplace_back(extractNumber(json, i, line, col));
        } else if (c == 't') {
            auto key = json.substr(i, 4);
            if (key != "true") {
                throw JException::ParseJsonError("Unexpected keyword \"" +
                                     key + "\" at line " + std::to_string(line) +
                                     " col " + std::to_string(col) + "!");
            }
            tokens.emplace_back("bool", "true", line, col);
            i += 4; col += 4;
        } else if (c == 'f') {
            auto key = json.substr(i, 5);
            if (key != "false") {
                throw JException::ParseJsonError("Unexpected keyword \"" +
                                     key + "\" at line " + std::to_string(line) +
                                     " col " + std::to_string(col) + "!");
            }
            tokens.emplace_back("bool", "false", line, col);
            i += 5; col += 5;
        } else if (c == 'n') {
            auto key = json.substr(i, 4);
            if (key != "null") {
                throw JException::ParseJsonError("Unexpected keyword \"" +
                                     key + "\" at line " + std::to_string(line) +
                                     " col " + std::to_string(col) + "!");
            }
            tokens.emplace_back("null", "", line, col);
            i += 4; col += 4;
        } else {
            throw JException::ParseJsonError("Unexpected character '" +
                                 std::string(1, c) + "' at line " + std::to_string(line) +
                                 " col " + std::to_string(col) + "!");
        }
        if (check_begin && !tokens.empty()) {
            bool b = (tokens.front().type == "{" || tokens.front().type == "[");
            if (!b) {
                throw JException::ParseJsonError("The JSON text does not start with '{' or '['!");
            }
            check_begin = false;
        }
    }
    if (enclosed_2) {
        throw JException::ParseJsonError("Redundant enclosing character '" + temp_token_2.type + "' at line " +
                             std::to_string(temp_token_2.line) + " col " +
                             std::to_string(temp_token_2.col) + "!");
    }
    if (enclosed_1) {
        throw JException::ParseJsonError("Redundant enclosing character '" + temp_token_1.type + "' at line " +
                             std::to_string(temp_token_1.line) + " col " +
                             std::to_string(temp_token_1.col) + "!");
    }
    if (end_pos < tokens.size() - 1) {
        throw JException::ParseJsonError("Redundant enclosing character '" + tokens[end_pos + 1].type + "' at line " +
                             std::to_string(tokens[end_pos + 1].line) + " col " +
                             std::to_string(tokens[end_pos + 1].col) + "!");
    }
    return tokens;
}

Json::JParser::Token Json::JParser::extractString(const std::string &json, size_t &pos,
                                                  uint32_t &line, uint32_t &col) {
    size_t start_pos = ++pos, end_pos = 0;
    size_t begin_line = line, begin_col = ++col;
    auto _size = json.size();
    while (pos < _size) {
        auto ch = json[pos++];
        col++;
        if (ch == '"') {
            end_pos = pos - 1;
            return {"string", json.substr(start_pos, end_pos - start_pos), begin_line, begin_col};
        } else if (ch == '\n') {
            throw JException::ParseJsonError("The character '\\n' is not supported at line " +
                                    std::to_string(line) + " col " + std::to_string(col) + "!");
        }
    }
    throw JException::ParseJsonError("The character '\"' is not enclosed at line " + std::to_string(begin_line) +
                         " col " + std::to_string(begin_col - 1) + "!");
}

Json::JParser::Token Json::JParser::extractNumber(const std::string &json, size_t &pos,
                                                  uint32_t &line, uint32_t &col) {
    size_t start_pos = pos, end_pos = 0;
    size_t begin_line = line, begin_col = col;
    auto _size = json.size();
    bool is_minus = false, is_point = false;
    if (json[pos] == '0' && isdigit(json[pos + 1])) {
        throw JException::ParseJsonError("The number can not start with the digit '0' at line " + std::to_string(line) +
                             " col " + std::to_string(col - 1) + "!");
    }
    while (pos < _size) {
        auto ch = json[pos++];
        col++;
        if (ch == '-') {
            if (is_minus) {
                throw JException::ParseJsonError("The number is not allowed to have repeated '-' characters at line " + std::to_string(line) +
                                     " col " + std::to_string(col - 1) + "!");
            }
            else is_minus = true;
        } else if (ch == '.') {
            if (is_point) {
                throw JException::ParseJsonError("The number is not allowed to have repeated '.' characters at line " + std::to_string(line) +
                                     " col " + std::to_string(col - 1) + "!");
            } else {
                is_point = true;
            }
        } else if (!isdigit(ch)) {
            col--;
            end_pos = --pos;
            break;
        }
    }
    auto cnt = end_pos - start_pos;
    if (cnt <= 0) {
        throw JException::ParseJsonError("The JSON context does not end with '}'!");
    }
    return {"number", json.substr(start_pos, cnt), begin_line, begin_col};
}

bool Json::JParser::hasLastOfType(const std::vector<Token> &tokens, const std::string &type,
                                  const std::string &ends_with_type) {
    size_t _size = tokens.size();
    while (--_size) {
        if (tokens[_size].type == type) return true;
        if (!ends_with_type.empty() && tokens[_size].type == ends_with_type) return false;
    }
    return false;
}

Json::JObject Json::JParser::parseObject(const std::vector<Token> &tokens, size_t &pos) {
    Json::JObject result;
    auto line = tokens[pos].line, col = tokens[pos].col;
    if (tokens[pos].type != "{") {
        throw JException::ParseJsonError("The Object is not start with \'{\' at line " +
                             std::to_string(tokens[pos].line) + " col " +
                             std::to_string(tokens[pos].col) + "!");
    }
    pos += 1;
    while (pos < tokens.size()) {
        std::string key;
        if (tokens[pos].type == "}") {
            if (tokens[pos - 1].type == ",")
                throw JException::ParseJsonError("The Object is not completed at line " +
                                 std::to_string(tokens[pos - 1].line) + " col " +
                                 std::to_string(tokens[pos - 1].col) + "!");
            else
                return result;
        }

        if (tokens[pos].type != "string") {
            throw JException::ParseJsonError("Expected '" + tokens[pos].type + "' at line " +
                                 std::to_string(tokens[pos].line) + " col " +
                                 std::to_string(tokens[pos].col) + "! Next one should be the key name!");
        }
        key = tokens[pos].value;
        pos++;
        if (tokens[pos].type != ":") {
            throw JException::ParseJsonError("Expected '" + tokens[pos].type + "' at line " +
                                 std::to_string(tokens[pos].line) + " col " +
                                 std::to_string(tokens[pos].col) + "! Next one should be the ':'!");
        }
        pos++;
        if (tokens[pos].type == "[") {
            result.set(key, std::make_shared<JArray>(parseArray(tokens, pos)));
        } else if (tokens[pos].type == "{") {
            result.set(key, std::make_shared<JObject>(parseObject(tokens, pos)));
        } else {
            result.set(key, parseValue(tokens[pos]));
        }
        pos++;
        if (tokens[pos].type == "}") {
            return result;
        } else if (tokens[pos].type == ",") {
            pos++;
            continue;
        }
    }
    throw JException::ParseJsonError("There is still an uncompleted object from the character '{' at line " +
                         std::to_string(line) + " col " + std::to_string(col) + "!");
}

Json::JValue Json::JParser::parseValue(const Json::JParser::Token &token) {
    if (token.type == "string") {
        auto s = strToEscape(token.value);
        return s;
    } else if (token.type == "number") {
        if (token.value.find('.') != std::string::npos) {
            return std::stod(token.value);
        } else {
            return std::stoll(token.value);
        }
    } else if (token.type == "bool") {
        if (token.value == "true") {
            return true;
        } else if (token.value == "false") {
            return false;
        }
    } else if (token.type == "null") {
        return std::monostate{};
    } else if (token.type == "[") {
        return std::monostate{};
    } else if (token.type == "{") {
        return std::monostate{};
    } else {
        throw JException::ParseJsonError("Can't parse value type '" + token.type + "' at line " +
                             std::to_string(token.line) + " col " +
                             std::to_string(token.col) + "!");
    }
    return std::monostate{};
}

Json::JArray Json::JParser::parseArray(const std::vector<Token> &tokens, size_t &pos) {
    Json::JArray result;
    auto line = tokens[pos].line, col = tokens[pos].col;
    if (tokens[pos].type != "[") {
        throw JException::ParseJsonError("The Array is not start with \'{\' at line " +
                             std::to_string(tokens[pos].line) + " col " +
                             std::to_string(tokens[pos].col) + "!");
    }
    pos++;
    while (pos < tokens.size()) {
        std::string key;
        if (tokens[pos].type == "]" && tokens[pos - 1].type == ",") {
            throw JException::ParseJsonError("The Array is not completed at line " +
                                 std::to_string(tokens[pos - 1].line) + " col " +
                                 std::to_string(tokens[pos - 1].col) + "!");
        }
        if (tokens[pos].type == "[") {
            result.append(std::make_shared<JArray>(parseArray(tokens, pos)));
        } else if (tokens[pos].type == "{") {
            result.append(std::make_shared<JObject>(parseObject(tokens, pos)));
        } else if (tokens[pos].type == "]") {
            return result;
        } else {
            result.append(parseValue(tokens[pos]));
        }
        pos++;
        if (tokens[pos].type == "]") {
            return result;
        } else if (tokens[pos].type == ",") {
            pos++;
            continue;
        } else if (tokens[pos].type == ":") {
            throw JException::ParseJsonError("Unexpected character ':' in array at line " +
                                 std::to_string(tokens[pos].line) + " col " +
                                 std::to_string(tokens[pos].col) + "!");
        } else {
            throw JException::ParseJsonError("There is still an uncompleted array from the character '[' at line " +
                                 std::to_string(line) + " col " + std::to_string(col) + "!");
        }
    }
    throw JException::ParseJsonError("There is still an uncompleted array from the character '[' at line " +
                         std::to_string(line) + " col " + std::to_string(col) + "!");
}

std::string Json::escToString(const std::string &str) {
    std::string result;
    size_t pos = 0;
    while (pos < str.size()) {
        if (str[pos] == '\\') {
            result += "\\\\";
        } else if (str[pos] == '\t') {
            result += "\\t";
        } else if (str[pos] == '\r') {
            result += "\\r";
        } else if (str[pos] == '\n') {
            result += "\\n";
        } else if (str[pos] == '\f') {
            result += "\\f";
        } else if (str[pos] == '\b') {
            result += "\\b";
        } else if (str[pos] == '"') {
            result += "\\\"";
        } else if (str[pos] == '\'') {
            result += "\\'";
        } else {
            result += str[pos];
        }
        pos++;
    }
    return result;
}

std::string Json::strToEscape(const std::string &str) {
    std::string result, s = str;
    size_t pos = 0;
    while (pos < str.size()) {
        if (s[pos++] == '\\') {
            if (s[pos] == '\\' ) {
                result += "\\";
            } else if (s[pos] == 't') {
                result += '\t';
            } else if (s[pos] == 'r') {
                result += '\r';
            } else if (s[pos] == 'n') {
                result += '\n';
            } else if (s[pos] == 'f') {
                result += '\f';
            } else if (s[pos] == 'b') {
                result += '\b';
            } else if (s[pos] == '"') {
                result += '"';
            } else if (s[pos] == '\'') {
                result += '\'';
            }
            pos++;
        } else {
            result += s[pos - 1];
        }
    }
    return result;
}


