#ifndef ChessPlusPlusBoardConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusBoardConfigurationManagerClass_HeaderPlusPlus

#include "Configuration.hpp"

namespace chesspp
{
    namespace config
    {
        class GraphicsConfig : public Configuration
        {
        public:
            GraphicsConfig()
            : Configuration("config/graphics.json")
            {
            }
            virtual ~GraphicsConfig() = default;

            template<typename... Args>
            std::string const &spritePath(Args... const &path) const
            {
                auto &val = navigate(reader()["chesspp"], path...);
                if(val.type() != json_string)
                {
                    return reader()["chesspp"]["missing"];
                }
                return val;
            }
            template<typename... Args>
            std::map<std::string, JsonReader::NestedValue const &> spritePaths(Args... const &path) const
            {
                return navigate(reader()["chesspp"], path...).object();
            }

        private:
            template<typename First, typename... Rest>
            static JsonReader::NestedValue const &navigate(JsonReader::NestedValue const &v, First const &first, Rest... const &rest)
            {
                return navigate(v[first], rest...);
            }
            template<typename Final>
            static JsonReader::NestedValue const &navigate<Final>(JsonReader::NestedValue const &v, Final const &final)
            {
                return v[final];
            }
        };
    }
}

#endif
