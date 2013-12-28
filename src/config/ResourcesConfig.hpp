#ifndef ChessPlusPlusResourcesConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusResourcesConfigurationManagerClass_HeaderPlusPlus

#include "Configuration.hpp"
#include "res/ResourceManager.hpp"

namespace chesspp
{
    namespace config
    {
        class ResourcesConfig : public Configuration
        {
            ResourceManager res;

        public:
            ResourcesConfig()
            : Configuration("config/graphics.json")
            , res(*this)
            {
            }

            RsourceManager &resources()
            {
                return res;
            }
        };
    }
}

#endif
