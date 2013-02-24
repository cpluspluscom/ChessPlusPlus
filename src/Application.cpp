#include "Application.h"
#include <iostream>

namespace chesspp
{
    Application::Application()
    :  	display(sf::VideoMode(640, 640), "ChessPlusPlus"), 
	running(true),
	state(new AppStateGame(this))
    {
    }

    int Application::Exec()
    {
        sf::Event Event;
        while(running)
        {
            while(display.pollEvent(Event)){
                state->OnEvent(Event);
		    
		switch(Event.type){
		case sf::Event::Closed:
			running = false;
			break;
		default:
			break;
		}
	    }

            state->OnRender(display);
	    display.display();
        }
        
        return 0;
    }

    Application::~Application()
    {
	delete state; //Even if it's null, no matter.
    } 
}