#ifndef _APPSTATEMANAGER_H
	#define _APPSTATEMANAGER_H
#include "SFML.hpp"
#include "AppState.h"
#include "AppStateGame.h"

namespace chesspp
{
    //enumeration for all of the states in the game.
    enum {
        APPSTATE_NONE = 0,
        APPSTATE_INTRO,
        APPSTATE_GAME,
        APPSTATE_OUTRO
    };

    class AppStateManager
    {
    public:
        static void onEvent(sf::Event *Event);
        static void onLoop();
        static void onRender(sf::RenderWindow *display);

        static AppState *getActiveAppState() {return activeAppState;}
        static void setActiveAppState(int ID);
    private:
        static AppState *activeAppState;
    }; 
}

#endif