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
        /**
         * \brief
         * Handles the start screen/main menu for the game.
         */
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
            /**
             * \brief
             * Construct from the Application and sf::RenderWindow to be used.
             * 
             * \param app The Application owning this instance, must outlive this instance.
             * \param display The sf::RenderWindow use during onRender(), must outlive this
             * instance.
             */
            StartMenuState(Application &app, sf::RenderWindow &display);

            /**
             * \brief
             * Renders the menu title and menu buttons.
             */
            virtual void onRender() override;

            /**
             * \brief
             * Handles clicking on the menu buttons.
             */
            virtual void onLButtonReleased(int x, int y) override;
            virtual void onMouseMoved(int x, int y) override;
            virtual void onKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) override;
        };
    }
}

#endif
