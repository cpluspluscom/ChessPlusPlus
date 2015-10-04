#ifndef chesspp_res_ResourcesManager_HeaderPlusPlus
#define chesspp_res_ResourcesManager_HeaderPlusPlus

#include "config/Configuration.hpp"
#include "util/Utilities.hpp"

#include <map>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <tuple>
#include <memory>

namespace chesspp
{
    namespace res
    {
        /**
         * \brief
         * Manages resources used by the application.
         */
        class ResourceManager final
        {
            config::Configuration &conf;

        public:
            /**
             * \brief
             * Constructs from a chesspp::config::Configuration
             * 
             * \param conf_ the chesspp::config::Conriguration - it is referenced, not copied.
             */
            ResourceManager(config::Configuration &conf_) noexcept
            : conf(conf_) //can't use {}
            {
            }

            /**
             * \brief
             * The base class for all resource classes.
             * 
             * \par Requirements
             * Deriving classes must have a public constructor that accepts one parameter in the
             * form of `configuration.setting(path...)`. In other words, the result of
             * chesspp::config::Configuration::setting() should be able to be passed as the only
             * argument to construct the resource.
             */
            class Resource
            {
            public:
                virtual ~Resource() = 0;
            };

        private:
            using Res_t = std::map<std::pair<std::string, std::type_index>, std::unique_ptr<Resource>>;
            Res_t res;

        public:
            /**
             * \brief
             * Obtains a resource for a config setting, constructing it if it does not yet
             * exist.
             * 
             * Example invocation:
             * 
             *     using Font_res = res::SfmlFileResource<sf::Font>;
             *     ResourceManager &resmanager = blah;
             *     Font_res &fontres = resmanager.from_config<Font_res>("menu", "font");
             *     sf::Font font (fontres);
             *     //...
             * 
             * \tparam ResT The type of the Resource to construct or return.
             * \tparam Path deduced by the compiler from the argument list.
             * \param path The path, forwarded to chesspp::config::Configuration::setting()
             * \return a reference to the resource, of type ResT
             */
            template<typename ResT, typename... Path>
            auto from_config(Path const &... path)
            -> typename std::enable_if
            <
                std::is_base_of<Resource, ResT>::value,
                ResT &
            >::type
            {
                Res_t::key_type key {util::path_concat(std::string("\0", 1), path...), typeid(ResT)};
                if(res.find(key) == std::end(res))
                {
                    res.emplace(key, Res_t::mapped_type{new ResT{conf.setting(path...)}});
                }
                //This cast is guaranteed to be correct
                return static_cast<ResT &>(*res[key]);
            }
        };
        inline ResourceManager::Resource::~Resource() = default;
    }
}

#endif
