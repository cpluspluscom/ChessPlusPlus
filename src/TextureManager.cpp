#include <TextureManager.hpp>


namespace chesspp
{
    //Structure used by std::shared_ptr to delete an sf::Texture.
    //This isn't needed because std::default_delete does the same thing.
    //Using it for debugging purposes, though.
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

  //Method that loads an sf::Texture from file name 'location'.
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
