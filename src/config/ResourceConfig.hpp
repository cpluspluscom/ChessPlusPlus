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
            : Configuration("config/chesspp/graphics.json")
            {
            }
            virtual ~GraphicsConfig() = default;

            std::string normalize(std::string const &path) const
            {
                return res_path + path;
            }
            template<typename... Args>
            std::string spritePath(Args const &... path) const
            {
                auto val = reader.navigate(path...);
                if(val.type() != json_string)
                {
                    return normalize(reader()["chesspp"]["missing"]);
                }
                return normalize(val);
            }
            //Must normalize return value
            template<typename... Args>
            auto spritePaths(Args const &... path) const -> std::map<std::string, util::JsonReader::NestedValue>
            {
                return reader.navigate(path...).object();
            }
        };
    }
}

#endif
