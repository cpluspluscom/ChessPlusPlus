#ifndef TextureManagerClass_HeaderPlusPlus
#define TextureManagerClass_HeaderPlusPlus

#include "ResourceManager.hpp"
#include "SFML.hpp"

#include <iostream>


namespace chesspp
{
    struct TextureDeleter
    {
        //Structure used by std::shared_ptr to delete an sf::Texture.  This isn't needed because std::default_delete does the same thing.  Using it for debugging purposes, though.
        void operator()(sf::Texture *texture) noexcept;
    };

    class TextureManager : public ResourceManager<sf::Texture, std::string, TextureDeleter>
    {
        TextureManager() noexcept;

        //no copying
        TextureManager(TextureManager const &) = delete;
        TextureManager &operator=(TextureManager const &) = delete;

    public:
        static TextureManager &instance() noexcept; //singleton class

    protected:
        //Method that loads an sf::Texture from file name 'location'.
        virtual sf::Texture *onLoadResource(std::string const &location) noexcept override;
    };
}

#endif
