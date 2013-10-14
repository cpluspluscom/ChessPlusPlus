#ifndef ChessPlusPlusGraphicsConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusGraphicsConfigurationManagerClass_HeaderPlusPlus

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
            std::string spritePath(Args const &... path) const
            {
                auto val = reader.navigate("chesspp", path...);
                if(val.type() != json_string)
                {
                    return reader()["chesspp"]["missing"];
                }
                return res_path + std::string(val);
            }
            template<typename... Args>
            std::map<std::string, util::JsonReader::NestedValue> spritePaths(Args const &... path) const
            {
                return reader.navigate("chesspp", path...).object();
            }
        };
    }
}

#endif
