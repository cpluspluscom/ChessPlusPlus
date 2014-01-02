#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display)
    : AppState(display)
    , app(app)
    , menu_background(app.resourcesConfig().resources().from_config<Texture_res>("chesspp", "menu", "background"))
    , logo(app.resourcesConfig().resources().from_config<Texture_res>("chesspp", "logo"))
    , font(app.resourcesConfig().resources().from_config<Font_res>("chesspp", "menu", "font"))
    , start_text("Start", font, 75)
    , quit_text("Quit", font, 75)
    {   
        // Sets position at centered horizontally, down 10% vertically
        logo.setPosition(((display.getSize().x / 2) - (logo.getLocalBounds().width / 2)) , (display.getSize().y * .10));
        
        // Set up text
        start_text.setPosition(((display.getSize().x / 2) - (start_text.getLocalBounds().width / 2)) , (display.getSize().y * .35));
        start_text.setColor(sf::Color::Black);
        start_text.setStyle(sf::Text::Bold);
        
        quit_text.setPosition(((display.getSize().x / 2) - (quit_text.getLocalBounds().width / 2)) , (display.getSize().y * .47));
        quit_text.setColor(sf::Color::Black);
        quit_text.setStyle(sf::Text::Bold);
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
        // If clicked on Start button
        if(start_text.getGlobalBounds().contains(x,y))
        {
            std::clog << "State changing to ChessPlusPlus." << std::endl;
            app.changeState<chesspp::ChessPlusPlusState>(std::ref(app), std::ref(display));
        }
        
        // If clicked on Exit button
        if(quit_text.getGlobalBounds().contains(x,y))
        {
            std::clog << "Exiting from StartMenuState." << std::endl;
            app.stop();
        }
    }
    
}

