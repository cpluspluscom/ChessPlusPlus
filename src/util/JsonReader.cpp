#include "JsonReader.hpp"

namespace chesspp
{
    namespace util
    {
        JsonReader::JsonReader(std::istream &s)
        {
            if(!s)
            {
                throw Exception("stream given to JsonReader in bad state");
            }
            std::string str ((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
            json_settings options {0, 0, nullptr, nullptr, nullptr};
            char error[json_error_max];
            json = json_parse_ex(&options, str.c_str(), str.length(), error);
            if(json == nullptr)
            {
                //no manual cleanup needed
                throw Exception(std::string("Error loading JSON: ") + error);
            }
        }
        JsonReader::JsonReader(std::istream &&s)
        : JsonReader(s)
        {
        }
        JsonReader::JsonReader(JsonReader &&from)
        : json(from.json)
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
        : value(value_)
        {
        }

        json_type JsonReader::NestedValue::type() const noexcept
        {
            return value.type;
        }
        JsonReader::NestedValue JsonReader::NestedValue::parent() const
        {
            if(value.parent)
            {
                return *value.parent;
            }
            throw Exception("No parent json value");
        }

        JsonReader::NestedValue JsonReader::NestedValue::operator[](std::string const &name) const noexcept(noexcept(name.c_str()))
        {
            return value[name.c_str()];
        }
        JsonReader::NestedValue JsonReader::NestedValue::operator[](char const *name) const
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
        JsonReader::NestedValue::operator bool() const noexcept
        {
            return value;
        }
        JsonReader::NestedValue::operator double() const noexcept
        {
            return value;
        }

        json_value const &JsonReader::NestedValue::implementation() noexcept
        {
            return value;
        }

        JsonReader::NestedValue JsonReader::access() const noexcept
        {
            return *json;
        }
        JsonReader::NestedValue JsonReader::operator()() const noexcept
        {
            return access();
        }
    }
}

