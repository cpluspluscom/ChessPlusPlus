#include "TextureManager.hpp"


namespace chesspp
{
    void TextureDeleter::operator()(sf::Texture *texture) noexcept
    {
        std::clog << "Deleting texture - unique_ptr has been deleted." << std::endl;
        delete texture;
    }

    TextureManager::TextureManager() noexcept
    {
    }

    TextureManager &TextureManager::instance() noexcept
    {
        static TextureManager inst;
        return inst;
    }

  sf::Texture *TextureManager::onLoadResource(std::string const &location) noexcept
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
}
