#ifndef _APPLICATION_H
	#define _APPLICATION_H

#include "AppStateManager.h"
#include "SFMLEvent.h"
#include <iostream>

namespace chesspp
{
    class Application : public SFMLEvent
    {
    public:
        Application() : running(true) {}

        Application(const Application&) {}
        Application &operator=(const Application&) {}

        bool onInit();
        void onEvent(sf::Event *Event);
        void onLoop();
        void onRender();
        void onCleanup();

        int Exec();

        virtual void OnClosed(); //example of Event handling.

    private:
        sf::RenderWindow *display;
        bool running;
    }; 
}

#endif