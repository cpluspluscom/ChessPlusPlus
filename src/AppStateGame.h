#ifndef _APPSTATEGAME_H
	#define _APPSTATEGAME_H
#include "SFML.hpp"
#include "TextureManager.h"

#ifdef _DEBUG
	#include <iostream>
	using std::cout; using std::cin; using std::endl;
#endif

namespace chesspp
{
    class AppStateGame : public AppState
    {
    public:
        AppStateGame() {}
        virtual ~AppStateGame() {}
        
        virtual int id();
        virtual void OnRender(sf::RenderWindow &display);
	
    private:
        //members of game can go here, board, etc etc.
    }; 
}

#endif