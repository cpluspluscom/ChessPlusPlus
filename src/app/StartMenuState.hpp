#ifndef ChessPlusPlus_App_StartMenuState_HeaderPlusPlus
#define ChessPlusPlus_App_StartMenuState_HeaderPlusPlus

/**
  * Class representing a start menu for the Chess++.
  * If a new 'button' is added, the appropriate code needs to be added to onRender(),
  * onMouseMoved(), and onKeyPressed(). Look at those methods for an example.
 */

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

            sf::Text *selected_menu_item;

            void setSelectedMenuItem(sf::Text *item);

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
