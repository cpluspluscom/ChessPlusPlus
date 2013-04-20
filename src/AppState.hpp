#ifndef _APPSTATE_H
#define _APPSTATE_H

#include "SFMLEvent.hpp"
#include <SFML/Graphics.hpp>

namespace chesspp
{
    //pure virtual abstract base class for game state management.
    class AppState : public SFMLEvent
    {
    public:
        AppState(sf::RenderWindow *_display) : display(_display) {}
        virtual ~AppState() {}

        virtual int id() = 0;
        virtual void OnRender() = 0;

    protected:
        sf::RenderWindow *display;
    };
}

#include "AppStateGame.hpp"
/* Convenience header inclusion so we don't have to include each individual inheritor */

#endif
