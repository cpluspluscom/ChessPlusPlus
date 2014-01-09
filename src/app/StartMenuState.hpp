#ifndef ChessPlusPlus_App_StartMenuState_HeaderPlusPlus
#define ChessPlusPlus_App_StartMenuState_HeaderPlusPlus

#include "SFML.hpp"

#include "AppState.hpp"
#include "Application.hpp"
#include "Button.hpp"
#include "ButtonManager.hpp"

namespace chesspp
{
    namespace app
    {
        class StartMenuState : public AppState
        {
            Application &app;

            sf::Sprite menu_background;
            sf::Sprite logo;

            sf::Font font;

            Button start_text;
            Button quit_text;

            ButtonManager button_manager;

        public:
            StartMenuState(Application &app, sf::RenderWindow &display);

            virtual void onRender() override;

            virtual void onLButtonReleased(int x, int y) override;
            virtual void onMouseMoved(int x, int y) override;
            virtual void onKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) override;
        };
    }
}

#endif
