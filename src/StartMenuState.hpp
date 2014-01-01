#ifndef STARTMENUSTATE_H
#define STARTMENUSTATE_H

#include "SFML.hpp"

#include "AppState.hpp"
#include "ChessPlusPlusState.hpp"
#include "Application.hpp"
#include "config/GraphicsConfig.hpp"
#include "TextureManager.hpp"

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
            sf::Sprite menu_background;
            sf::Sprite logo;
            
            sf::Text start_text;
            sf::Text quit_text;
            sf::Font font;
            
            Application &app;
            config::GraphicsConfig gfx_config;
    };
}

#endif

