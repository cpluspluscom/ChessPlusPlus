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
                auto &val = reader.navigate("chesspp", path...);
                if(val.type() != json_string)
                {
                    return reader()["chesspp"]["missing"];
                }
                return val;
            }
            template<typename... Args>
            std::map<std::string, JsonReader::NestedValue> spritePaths(Args... const &path) const
            {
                return reader.navigate("chesspp", path...).object();
            }
        };
    }
}

#endif
