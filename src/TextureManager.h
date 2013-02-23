#ifndef _TEXTUREMANAGER_H
	#define _TEXTUREMANAGER_H
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#ifdef _DEBUG
	#include <iostream>
	using std::cout; using std::endl;
#endif
	
struct TextureDeleter
{
	//************************************
	// Method:    operator()
	// FullName:  TextureDeleter::operator()
	// Access:    public 
	// Returns:   void
	// Parameter: sf::Texture * texture
	//   Structure used by std::shared_ptr to delete an sf::Texture.
	//   This isn't needed because std::default_delete does the same thing.
	//   Using it for debugging purposes, though. 
	//************************************
	void operator()(sf::Texture *texture)
	{
		#ifdef _DEBUG
			cout << "Deleting texture -- ref count reached zero." << endl;
		#endif
		delete texture;
	}
};

class TextureManager : public ResourceManager<sf::Texture, TextureDeleter>
{
private:
	inline TextureManager() {}

	//no copying
	TextureManager(const TextureManager &);
	TextureManager &operator=(const TextureManager &);

public:
	static TextureManager &getInstance() //singleton class
	{
		static TextureManager instance;
		return instance;
	}

protected:
	//************************************
	// Method:    onLoadResource
	// FullName:  TextureManager::onLoadResource
	// Access:    protected 
	// Returns:   sf::Texture *
	// Parameter: const std::string & location
	//   Method that loads an sf::Texture from file name 'location'. 
	//************************************
	sf::Texture *onLoadResource(const std::string &location)
	{
		sf::Texture *ret = new sf::Texture();
		ret->loadFromFile(location);

		#ifdef _DEBUG
			cout << "Loaded " << location << " into memory." << endl;
		#endif

		return ret;
	}
};

#endif