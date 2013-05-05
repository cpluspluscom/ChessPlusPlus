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
            : Configuration("config.json")
            {
            }

            std::string getSpritePath(std::string const &name)
            {
                return res_path + std::string(reader()["chesspp"]["board"]["images"][name]);
            }
        };
    }
}

#endif
