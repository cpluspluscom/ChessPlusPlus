#ifndef STARTMENUSTATE_H
#define STARTMENUSTATE_H

#include "SFML.hpp"

#include "AppState.hpp"
#include "ChessPlusPlusState.hpp"
#include "Application.hpp"
#include "res/SfmlFileResource.hpp"


#include <iostream>
#include <memory>

namespace chesspp
{
    class StartMenuState : public AppState
    {
        public:
            StartMenuState(Application &app, sf::RenderWindow &display);
            
            virtual void onRender() override;
            
            virtual void onLButtonReleased(int x, int y) override;
            
        private:
            using Font_res = res::SfmlFileResource<sf::Font>;
            using Texture_res = res::SfmlFileResource<sf::Texture>;
            
            Application &app;
            
            sf::Sprite menu_background;
            sf::Sprite logo;
            
            sf::Font &font;
            sf::Text start_text;
            sf::Text quit_text;
    };
}

#endif

