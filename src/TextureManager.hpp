#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <iostream>

#include "ResourceManager.hpp"
#include "SFML.hpp"


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
        TextureManager(const TextureManager &) = delete;
        TextureManager &operator=(const TextureManager &) = delete;

    public:
        static TextureManager &getInstance() noexcept //singleton class
        {
            static TextureManager instance;
            return instance;
        }

    protected:
        //Method that loads an sf::Texture from file name 'location'.
        virtual sf::Texture *onLoadResource(const std::string &location) noexcept
        {
            sf::Texture *ret = new sf::Texture();
            if(!ret->loadFromFile(location))
            {
                std::clog << "Failed to load " << location << std::endl;
                return nullptr;
            }
            std::clog << "Loaded " << location << " into memory." << std::endl;
            return ret;
        }
    };
}

#endif
