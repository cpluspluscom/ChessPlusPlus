#include "AppStateManager.h"

namespace chesspp
{
    AppState *AppStateManager::activeAppState = 0;

    void AppStateManager::setActiveAppState(int ID)
    {
        if(activeAppState) activeAppState->onDeactivate();
        switch(ID)
        {
        case APPSTATE_NONE:
            activeAppState = NULL;
            break;
        case APPSTATE_INTRO:
            //activeAppState = AppStateIntro::getInstance(); <-- placeholder
            break;
        case APPSTATE_GAME:
            activeAppState = AppStateGame::getInstance(); //<-- placeholder
            break;
        case APPSTATE_OUTRO:
            //activeAppState = AppStateOutro::getInstance(); <-- placeholder
            break;
        default:
            break;
        }
        if(activeAppState) activeAppState->onActivate();
    }

    void AppStateManager::onEvent(sf::Event *Event)
    {
        if(activeAppState) activeAppState->onEvent(Event);
    }
    void AppStateManager::onLoop()
    {
        if(activeAppState) activeAppState->onLoop();
    }
    void AppStateManager::onRender(sf::RenderWindow *display)
    {
        if(activeAppState) activeAppState->onRender(display);
    } 
}