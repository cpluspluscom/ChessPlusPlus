#ifndef __JavaScriptObjectNotation_Reader_HeaderPlusPlus__
#define __JavaScriptObjectNotation_Reader_HeaderPlusPlus__

#include <string>
#include <istream>
#include <streambuf>
#include <json.h>
#include <cstdint>

#include "Exception.hpp"

namespace chesspp
{
    namespace util
    {
        class JsonReader
        {
            json_value *json {nullptr};
        public:
            JsonReader(std::istream &s) noexcept(false)
            {
                std::string str ((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
                json_settings options {};
                char error[128]; //128 from json.c implementation, subject to change
                json = json_parse_ex(&options, str.c_str(), str.length(), error);
                if(json == nullptr)
                {
                    //no manual cleanup needed
                    throw Exception(std::string("Error loading JSON: ") + error, Exception(str)); //attached JSON as 'caused by'
                }
            }
            JsonReader(std::istream &&s) noexcept(false) : JsonReader(s)
            {
            }
            ~JsonReader() noexcept
            {
                json_value_free(json), json = nullptr;
            }

            class NestedValue
            {
                friend class ::chesspp::util::JsonReader;
                json_value const&value;
                NestedValue(json_value const&value) noexcept : value(value)
                {
                }
                NestedValue &operator=(NestedValue const&) noexcept = delete;
            public:
                NestedValue(NestedValue const&) noexcept = default;
                NestedValue(NestedValue &&) noexcept = default;
                NestedValue &operator=(NestedValue &&) noexcept = default;
                ~NestedValue() noexcept = default;
                
                json_type type() const noexcept //may wish to add an abstraction layer between json-parser
                {
                    return value.type;
                }
                NestedValue parent() const noexcept(false)
                {
                    if(value.parent)
                    {
                        return *value.parent;
                    }
                    throw Exception("No parent json value");
                }
                
                NestedValue operator[](std::string const&name) const noexcept(noexcept(name.c_str()))
                {
                    return value[name.c_str()];
                }
                NestedValue operator[](char const*name) //without this, ambiguity occurs
                {
                    return value[name];
                }
                NestedValue operator[](std::size_t index) const noexcept
                {
                    return value[static_cast<int>(index)];
                }
                operator std::string() const noexcept(noexcept(std::string("")))
                {
                    return static_cast<char const*>(value);
                }
                //I tried an approach with templates, but the compiler was never able to deduce the corect template argument
                operator std::  int8_t() const noexcept { return static_cast<std::  int8_t>(static_cast<json_int_t>(value)); }
                operator std:: uint8_t() const noexcept { return static_cast<std:: uint8_t>(static_cast<json_int_t>(value)); }
                operator std:: int16_t() const noexcept { return static_cast<std:: int16_t>(static_cast<json_int_t>(value)); }
                operator std::uint16_t() const noexcept { return static_cast<std::uint16_t>(static_cast<json_int_t>(value)); }
                operator std:: int32_t() const noexcept { return static_cast<std:: int32_t>(static_cast<json_int_t>(value)); }
                operator std::uint32_t() const noexcept { return static_cast<std::uint32_t>(static_cast<json_int_t>(value)); }
                operator std:: int64_t() const noexcept { return static_cast<std:: int64_t>(static_cast<json_int_t>(value)); }
                operator std::uint64_t() const noexcept { return static_cast<std::uint64_t>(static_cast<json_int_t>(value)); }
                operator bool() const noexcept
                {
                    return value;
                }
                operator double() const noexcept
                {
                    return value;
                }
            };
            
            NestedValue access() const noexcept
            {
                return *json;
            }
            NestedValue operator()() const noexcept
            {
                return access();
            }

            json_value *&implementation() noexcept //only for extreme-use cases
            {
                return json;
            }
        };
    }
}

#endif
