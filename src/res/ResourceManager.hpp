#ifndef GenericResourcesManagerClass_HeaderPlusPlus
#define GenericResourcesManagerClass_HeaderPlusPlus

#include "config/Configuration.hpp"

#include <map>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <memory>

namespace chesspp
{
    class ResourceManager final
    {
        Configuration &conf;

    public:
        ResourceManager(Configuration &conf_) noexcept
        : conf(conf_)
        {
        }

        class Resource
        {
            virtual ~Resource() = 0;
        };

    private:
        template<typename... Path>
        class ResMap final
        {
        };
        using Res_t = std::map<std::pair<std::type_index, std::type_index>, std::unqiue_ptr<Resource>>;
        Res_t res;

    public:
        template<typename ResT, typename... Path>
        auto get(Path const &... path)
        -> typename std::enable_if
        <
            std::is_base_of<Resource, ResT>::value,
            ResT &
        >::type
        {
            Res_t::key_type key
            {
                typeid(ResMap<Path...>),
                typeid(ResT)
            };
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

#endif
