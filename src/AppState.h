#ifndef _APPSTATE_H
#define _APPSTATE_H

#include <SFML/Graphics.hpp>

namespace chesspp
{
    //pure virtual abstract base class for game state management. 
    class AppState
    {
    public:
        AppState() {}
        virtual ~AppState() {}

        virtual void OnEvent(sf::Event& event) {} //Nothing by default
        virtual int id() = 0;
        virtual void OnRender(sf::RenderWindow &display) = 0;
    }; 
}

#include "AppStateGame.h"
/* Convenience header inclusion so we don't have to include each individual inheritor */

#endif