#include "JsonReader.hpp"

#include <json.h>

#include <istream>
#include <stdexcept>

namespace chesspp
{
    namespace util
    {
        JsonReader::JsonReader(std::istream &s)
        {
            if(!s)
            {
                throw std::invalid_argument{"stream given to JsonReader in bad state"};
            }
            std::string str ((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
            json_settings options {0U, 0, nullptr, nullptr, nullptr, 0U};
            char error[json_error_max];
            json = json_parse_ex(&options, str.c_str(), str.length(), error);
            if(!json)
            {
                //no manual cleanup needed
                throw std::runtime_error{std::string("Error loading JSON: ") + error};
            }
        }
        JsonReader::JsonReader(std::istream &&s)
        : JsonReader{s}
        {
        }
        JsonReader::JsonReader(JsonReader &&from)
        : json{from.json}
        {
            from.json = nullptr;
        }
        JsonReader &JsonReader::operator=(std::istream &&s)
        {
            *this = JsonReader(s); //move assign
            return *this;
        }
        JsonReader &JsonReader::operator=(JsonReader &&from)
        {
            std::swap(json, from.json);
            return *this;
        }
        JsonReader::~JsonReader()
        {
            json_value_free(json), json = nullptr;
        }
        JsonReader::NestedValue::NestedValue(json_value const &value_) noexcept
        : value(value_) //can't use {}
        {
        }
        JsonReader::Type JsonReader::NestedValue::type() const noexcept
        {
            switch(value.type)
            {
                case json_object:  return Type::Object;
                case json_array:   return Type::Array;
                case json_integer: return Type::Integer;
                case json_double:  return Type::Double;
                case json_string:  return Type::String;
                case json_boolean: return Type::Boolean;
                case json_null:    return Type::Null;
                default:           return Type::None;
            }
        }
        JsonReader::NestedValue JsonReader::NestedValue::parent() const
        {
            if(value.parent)
            {
                return *value.parent;
            }
            throw std::domain_error{"No parent json value"};
        }
        JsonReader::NestedValue JsonReader::NestedValue::operator[](std::string const &name) const noexcept(noexcept(name.c_str()))
        {
            return value[name.c_str()];
        }
        JsonReader::NestedValue JsonReader::NestedValue::operator[](char const *name) const noexcept
        {
            return value[name];
        }
        std::size_t JsonReader::NestedValue::length() const noexcept
        {
            if(value.type == json_array)
            {
                return value.u.array.length;
            }
            return 0;
        }
        JsonReader::NestedValue JsonReader::NestedValue::operator[](std::size_t index) const noexcept
        {
            return value[static_cast<int>(index)];
        }
        std::map<std::string, JsonReader::NestedValue> JsonReader::NestedValue::object() const
        {
            std::map<std::string, NestedValue> obj;
            if(value.type == json_object)
            {
                for(std::size_t i = 0; i < value.u.object.length; ++i)
                {
                    obj.insert(std::make_pair<std::string const, NestedValue>(value.u.object.values[i].name, *value.u.object.values[i].value));
                }
            }
            return obj;
        }
        JsonReader::NestedValue::operator std::string() const noexcept(noexcept(std::string("")))
        {
            return static_cast<char const *>(value);
        }
        JsonReader::NestedValue::operator std::  int8_t() const noexcept { return static_cast<std::  int8_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std:: uint8_t() const noexcept { return static_cast<std:: uint8_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std:: int16_t() const noexcept { return static_cast<std:: int16_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std::uint16_t() const noexcept { return static_cast<std::uint16_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std:: int32_t() const noexcept { return static_cast<std:: int32_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std::uint32_t() const noexcept { return static_cast<std::uint32_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std:: int64_t() const noexcept { return static_cast<std:: int64_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator std::uint64_t() const noexcept { return static_cast<std::uint64_t>(static_cast<json_int_t>(value)); }
        JsonReader::NestedValue::operator bool() const noexcept
        {
            return value;
        }
        JsonReader::NestedValue::operator double() const noexcept
        {
            return value;
        }
        JsonReader::NestedValue JsonReader::access() const noexcept
        {
            return *json;
        }
    }
}
