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
	Application* app;    
	    
    public:
        AppStateGame(Application*);
        virtual ~AppStateGame() {}
        
        virtual int id();
        virtual void OnRender(sf::RenderWindow &display);
    }; 
}

#endif