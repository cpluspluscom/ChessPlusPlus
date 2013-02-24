#ifndef _APPLICATION_H
	#define _APPLICATION_H

#include "AppStateManager.h"
#include "SFMLEvent.h"
#include <iostream>

namespace chesspp
{
    class Application : public SFMLEvent
    {
    protected:
	Application(const Application&);
        Application &operator=(const Application&);
	    
    public:
        Application() :  display(sf::VideoMode(640, 640), "ChessPlusPlus"), running(true) {}

        bool onInit();
        void onEvent(sf::Event *Event);
        void onLoop();
        void onRender();
        void onCleanup();

        int Exec();

        virtual void OnClosed(); //example of Event handling.

    private:
        sf::RenderWindow display;
        bool running;
    }; 
}

#endif