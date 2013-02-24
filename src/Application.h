#ifndef _APPLICATION_H
	#define _APPLICATION_H

#include "AppState.h"

namespace chesspp
{
    class Application
    {
	sf::RenderWindow display;
        bool running;
	AppState* state;
	
    public:  
	Application();
	~Application();
		
        int Exec();
    }; 
}

#endif