#ifndef GenericResourceManagerClass_HeaderPlusPlus
#define GenericResourceManagerClass_HeaderPlusPlus

#include "ResourceManager_impl.hpp"
#include "SFML.hpp"

#include <functional>
#include <typeinfo>
#include <iostream>

namespace chesspp
{

template<typename resource_type>
struct generic_deleter
{
    void operator()(resource_type *resource) noexcept
    {
        std::clog << typeid(resource_type).name()
                  << " has been deleted from a resource manager." 
                  << std::endl;
        delete resource;
    }
};

template<typename T>
struct sfml_resource_loader
{
  template<typename... Args>
  bool operator()(T& obj, Args&... args)
  {
    return obj.loadFromFile(std::forward<Args>(args)...);
  }
};

template<typename resource_type, 
         typename identifier_type, 
         typename loader_type = sfml_resource_loader<resource_type>
        >
class GenericResourceManager 
: public ResourceManager_impl<resource_type, 
                              identifier_type, 
                              generic_deleter<resource_type>
                             >
{

public:
    GenericResourceManager() = default;

    //no copying
    GenericResourceManager(GenericResourceManager const &) = delete;
    GenericResourceManager &operator=(GenericResourceManager const &) = delete;

protected:
    //Method that loads a resource from file name 'location'
    //using 'loader_type' to do so
    virtual resource_type *onLoadResource(std::string const &location) noexcept override
    {
        resource_type *ret = new resource_type();
        if(!loader_type()(*ret, location))
        {
            std::clog << "Failed to load type " << typeid(resource_type).name()
                      << " from location " << location << std::endl;;
            return delete ret, ret = nullptr;
        }
        std::clog << "Loaded a(n) " << typeid(resource_type).name()
                  << "from location " << location
                  << " into memory." << std::endl;
        return ret;
    } 
};

template<typename T> using ResourceManager_t = GenericResourceManager<T, std::string>;

ResourceManager_t<sf::Texture>       TextureManager;
ResourceManager_t<sf::Font>          FontManager;
ResourceManager_t<sf::SoundBuffer>   SoundBufferManager;

}; // namespace chesspp
#endif