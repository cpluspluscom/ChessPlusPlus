#ifndef _APPLICATION_H
    #define _APPLICATION_H

#include "AppState.hpp"

namespace chesspp
{
    class Application
    {
        sf::RenderWindow display;
        bool running;
        AppState* state;
        void OnEvent(sf::Event *Event);

    public:
        Application();
        ~Application();

        template<class NewState> void ChangeState()
        {
            delete state;
            state = new NewState;
        }
        int Exec();
    };
}

#endif
