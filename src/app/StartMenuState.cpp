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
        , start_text{"Start", font, 75}
        , quit_text {"Quit",  font, 75}
        , selected_menu_item{&start_text}
        {
            //Sets position at centered horizontally, down 10% vertically
            logo.setPosition      (((display.getSize().x/2) - (logo.getLocalBounds()      .width/2)), (display.getSize().y*0.10));

            //Set up text
            start_text.setPosition(((display.getSize().x/2) - (start_text.getLocalBounds().width/2)), (display.getSize().y*0.35));
            start_text.setColor(sf::Color::Blue);
            start_text.setStyle(sf::Text::Bold);

            quit_text.setPosition (((display.getSize().x/2) - (quit_text.getLocalBounds() .width/2)), (display.getSize().y*0.47));
            quit_text.setColor(sf::Color::Black);
            quit_text.setStyle(sf::Text::Bold);
        }

        void StartMenuState::onRender()
        \
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
            if(start_text.getGlobalBounds().contains(x,y))
            {
                std::clog << "State changing to ChessPlusPlus" << std::endl;
                return app.changeState<ChessPlusPlusState>(std::ref(app), std::ref(display));
            }

            //If clicked on Exit button
            if(quit_text.getGlobalBounds().contains(x,y))
            {
                std::clog << "Exiting from StartMenuState" << std::endl;
                return app.stop();
            }
        }

        void StartMenuState::onMouseMoved(int x, int y)
        {
            //If moused over Start button
            if(start_text.getGlobalBounds().contains(x,y))
            {
                setSelectedMenuItem(&start_text);
            }
            else if(quit_text.getGlobalBounds().contains(x,y))
            {
                setSelectedMenuItem(&quit_text);
            }
        }

        void StartMenuState::onKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system)
        {
            //If Enter (Return) key is pressed, perform action for currently selected button
            if(key == sf::Keyboard::Key::Return)
            {
                if(selected_menu_item == &start_text)
                {
                    std::clog << "State changing to ChessPlusPlus" << std::endl;
                    return app.changeState<ChessPlusPlusState>(std::ref(app), std::ref(display));
                }
                if(selected_menu_item == &quit_text)
                {
                    std::clog << "Exiting from StartMenuState" << std::endl;
                    return app.stop();
                }
            }

            //Allowed to 'cycle' through menu items with arrow keys
            if(key == sf::Keyboard::Key::Up)
            {
                if(selected_menu_item == &start_text)
                {
                    setSelectedMenuItem(&quit_text);
                }
                else if(selected_menu_item == &quit_text)
                {
                    setSelectedMenuItem(&start_text);
                }
            }
            if(key == sf::Keyboard::Key::Down)
            {
                if(selected_menu_item == &start_text)
                {
                    setSelectedMenuItem(&quit_text);
                }
                else if(selected_menu_item == &quit_text)
                {
                    setSelectedMenuItem(&start_text);
                }
            }

        }

        void StartMenuState::setSelectedMenuItem(sf::Text *item)
        {
            if(item == &start_text)
            {
                start_text.setColor(sf::Color::Blue);
                quit_text.setColor(sf::Color::Black);
                selected_menu_item = &start_text;
            }
            else if(item == &quit_text)
            {
                quit_text.setColor(sf::Color::Blue);
                start_text.setColor(sf::Color::Black);
                selected_menu_item = &quit_text;
            }
        }
    }
}
