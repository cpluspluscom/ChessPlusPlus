#ifndef ChessPlusPlusStartMenuState_HeaderPlusPlus
#define ChessPlusPlusStartMenuState_HeaderPlusPlus

#include "SFML.hpp"

#include "AppState.hpp"
#include "Application.hpp"

namespace chesspp
{
    namespace app
    {
        class StartMenuState : public AppState
        {
            Application &app;

            sf::Sprite menu_background;
            sf::Sprite logo;

            sf::Font &font;
            sf::Text start_text;
            sf::Text quit_text;

        public:
            StartMenuState(Application &app, sf::RenderWindow &display);

            virtual void onRender() override;

            virtual void onLButtonReleased(int x, int y) override;
        };
    }
}

#endif
