#include "StartMenuState.hpp"

#include "ChessPlusPlusState.hpp"
#include "res/SfmlFileResource.hpp"

#include <iostream>

namespace chesspp
{
    namespace app
    {
        using Font_res = res::SfmlFileResource<sf::Font>;
        using Texture_res = res::SfmlFileResource<sf::Texture>;
        StartMenuState::StartMenuState(Application &app_, sf::RenderWindow &display_)
        : AppState(display_) //can't use {}
        , app(app_)          //can't use {}
        , menu_background{app.resourcesConfig().resources().from_config<Texture_res>("menu", "background")}
        , logo           {app.resourcesConfig().resources().from_config<Texture_res>("menu", "title")     }
        , font           (app.resourcesConfig().resources().from_config<Font_res>   ("menu", "font")      ) //can't use {}
        , start_text{"Start", 75}
        , quit_text {"Quit", 75}
        {
            //Sets position at centered horizontally, down 10% vertically
            logo.setPosition((display.getSize().x/2) - (logo.getLocalBounds().width/2), display.getSize().y*0.10);

            //Set up text
            start_text.setPosition(display.getSize().x/2, display.getSize().y*0.35);
            start_text.setFont(font);

            quit_text.setPosition (display.getSize().x/2, display.getSize().y*0.47);
            quit_text.setFont(font);

            //Register buttons with button_manager
            button_manager.registerButton(start_text);
            button_manager.registerButton(quit_text);
            button_manager.setSelected(start_text);
        }

        void StartMenuState::onRender()
        {
            display.clear();
            display.draw(menu_background);
            display.draw(logo);
            display.draw(start_text);
            display.draw(quit_text);
        }

        void StartMenuState::onLButtonReleased(int x, int y)
        {
            //If clicked on Start button
            if(start_text.contains(x,y))
            {
                std::clog << "State Change: StartMenuState -> ChessPlusPlusState" << std::endl;
                return app.changeState<ChessPlusPlusState>(std::ref(app), std::ref(display));
            }

            //If clicked on Exit button
            if(quit_text.contains(x,y))
            {
                std::clog << "Exiting from StartMenuState" << std::endl;
                return app.stop();
            }
        }

        void StartMenuState::onMouseMoved(int x, int y)
        {
            //If moused over Start button
            if(start_text.contains(x,y))
            {
                button_manager.setSelected(start_text);
            }
            else if(quit_text.contains(x,y))
            {
                button_manager.setSelected(quit_text);
            }
        }

        void StartMenuState::onKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system)
        {
            //If Enter (Return) key is pressed, perform action for currently selected button
            if(key == sf::Keyboard::Key::Return)
            {
                if(button_manager.getSelected() == start_text)
                {
                    std::clog << "State changing to ChessPlusPlus" << std::endl;
                    return app.changeState<ChessPlusPlusState>(std::ref(app), std::ref(display));
                }
                if(button_manager.getSelected() == quit_text)
                {
                    std::clog << "Exiting from StartMenuState" << std::endl;
                    return app.stop();
                }
            }

            //Allowed to 'cycle' through menu items with arrow keys
            if(key == sf::Keyboard::Key::Up)
            {
                button_manager.cycleSelectedNext();
            }
            if(key == sf::Keyboard::Key::Down)
            {
                button_manager.cycleSelectedPrevious();
            }

        }
    }
}
