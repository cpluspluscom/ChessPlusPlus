#ifndef TextureManagerClass_HeaderPlusPlus
#define TextureManagerClass_HeaderPlusPlus

#include "ResourceManager.hpp"
#include "SFML.hpp"

#include <iostream>


namespace chesspp
{
    struct TextureDeleter
    {
        //Structure used by std::shared_ptr to delete an sf::Texture.
        //This isn't needed because std::default_delete does the same thing.
        //Using it for debugging purposes, though.
        void operator()(sf::Texture *texture) noexcept
        {
            std::clog << "Deleting texture - unique_ptr has been deleted." << std::endl;
            delete texture;
        }
    };

    class TextureManager : public ResourceManager<sf::Texture, std::string, TextureDeleter>
    {
        TextureManager() noexcept
        {
        }

        //no copying
        TextureManager(TextureManager const &) = delete;
        TextureManager &operator=(TextureManager const &) = delete;

    public:
        static TextureManager &instance() noexcept //singleton class
        {
            static TextureManager inst;
            return inst;
        }

    protected:
        //Method that loads an sf::Texture from file name 'location'.
        virtual sf::Texture *onLoadResource(std::string const &location) noexcept override
        {
            sf::Texture *ret = new sf::Texture(); //should change to std::shared_ptr eventually
            if(!ret->loadFromFile(location))
            {
                std::clog << "Failed to load " << location << std::endl;
                return delete ret, ret = nullptr;
            }
            std::clog << "Loaded " << location << " into memory." << std::endl;
            return ret;
        }
    };
}

#endif
