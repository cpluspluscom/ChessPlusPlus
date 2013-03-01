#ifndef _APPSTATEGAME_H
	#define _APPSTATEGAME_H
#include "SFML.hpp"
#include "TextureManager.h"
#include "board\Board.h"

#ifdef _DEBUG
	#include <iostream>
	using std::cout; using std::cin; using std::endl;
#endif

namespace chesspp
{
    class Application;
    class AppStateGame : public AppState
    {
	    Application* app;    

        // Adding some variables to avoid initializing for every render
        // I know that this doesn't go with the flow, but the only way I see it now.
        sf::Sprite background;
        sf::Sprite pieces;
        sf::Sprite validMove;

        std::string backgroundPath;
        std::string piecePath;
        std::string validMovePath;

        Board* board;
	    
    public:
        AppStateGame(Application* _app);
        virtual ~AppStateGame() {}
        
        virtual int id();
        virtual void OnRender(sf::RenderWindow &display);

        virtual void OnLButtonPressed(int x, int y);
        virtual void OnLButtonReleased(int x, int y);
        virtual void OnMouseMoved(int x, int y);
    }; 
}

#endif