#ifndef chesspp_config_ResourcesConfig_HeaderPlusPlus
#define chesspp_config_ResourcesConfig_HeaderPlusPlus

#include "Configuration.hpp"
#include "res/ResourceManager.hpp"

namespace chesspp
{
    namespace config
    {
        /**
         * \brief
         * Holds configuration for resources (graphics, fonts, etc)
         */
        class ResourcesConfig
        : public Configuration
        {
            res::ResourceManager res;

        public:
            /**
             * \brief
             * Loads resource configuration from "config/chesspp/resources.json"
             */
            ResourcesConfig()
            : Configuration{"config/chesspp/resources.json"}
            , res{*this}
            {
            }

            /**
             * \brief
             * Get the chesspp::res::ResourceManager
             * 
             * \return chesspp::res::ResourceManager
             */
            res::ResourceManager &resources() noexcept
            {
                return res;
            }
        };
    }
}

#endif
