#ifndef STARTMENUSTATE_H
#define STARTMENUSTATE

#include "SFML.hpp"

#include "AppState.hpp"
#include "Application.hpp"

#include <iostream>

namespace chesspp
{
    class StartMenuState : public AppState
    {
        public:
            StartMenuState(Application &app, sf::RenderWindow &display);
            
            virtual void onRender() override;
            
            virtual void onLButtonPressed(int x, int y) override;
            
        private:
            sf::Texture menuBackgroundTexture;
            sf::Sprite menuBackground;
            Application &app;
    };
}

#endif

