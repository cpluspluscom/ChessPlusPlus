#ifndef GenericResourcesManagerClass_HeaderPlusPlus
#define GenericResourcesManagerClass_HeaderPlusPlus

#include "config/Configuration.hpp"

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
        class ResourceManager final
        {
            config::Configuration &conf;

        public:
            ResourceManager(config::Configuration &conf_) noexcept
            : conf(conf_)
            {
            }

            class Resource
            {
            public:
                virtual ~Resource() = 0;
            };

        private:
            using Res_t = std::map<std::pair<std::string, std::type_index>, std::unique_ptr<Resource>>;
            Res_t res;

        public:
            template<typename ResT, typename... Path>
            auto from_config(Path const &... path)
            -> typename std::enable_if
            <
                std::is_base_of<Resource, ResT>::value,
                ResT &
            >::type
            {
                Res_t::key_type key {"", typeid(ResT)};
                if(res.find(key) == std::end(res))
                {
                    res.emplace(key, Res_t::mapped_type{new ResT{conf.setting(path...)}});
                }
                //This cast is guaranteed to be correct
                return static_cast<ResT &>(*res[key]);
            }
            template<typename ResT>
            auto from_path(std::string const &path)
            -> typename std::enable_if
            <
                std::is_base_of<Resource, ResT>::value,
                ResT &
            >::type
            {
                Res_t::key_type key {path, typeid(ResT)};
                if(res.find(key) == std::end(res))
                {
                    res.emplace(key, Res_t::mapped_type{new ResT{path}});
                }
            }
        };
        inline ResourceManager::Resource::~Resource() = default;
    }
}

#endif
