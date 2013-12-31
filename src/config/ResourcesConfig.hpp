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
            res::ResourceManager res;

        public:
            ResourcesConfig()
            : Configuration("config/chesspp/resources.json")
            , res(*this)
            {
            }

            res::ResourceManager &resources() noexcept
            {
                return res;
            }
        };
    }
}

#endif
