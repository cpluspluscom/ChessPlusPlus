#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display)
    : AppState(display)
    , app(app)
    , font(app.resourcesConfig().resources().from_config<Font_res>("chesspp", "menu", "font"))
    {
        // Load and initialize resources
        menu_background.setTexture(app.resourcesConfig().resources().from_config<Texture_res>("chesspp", "menu", "background"));
        logo.setTexture(app.resourcesConfig().resources().from_config<Texture_res>("chesspp", "logo"), true);
        
        // Sets position at centered horizontally, down 10% vertically
        logo.setPosition(((display.getSize().x / 2) - (logo.getLocalBounds().width / 2)) , (display.getSize().y * .10));

        start_text.setFont(font);
        quit_text.setFont(font);
        
        // Initialize text
        start_text.setString("Start");
        start_text.setCharacterSize(75);
        start_text.setPosition(((display.getSize().x / 2) - (start_text.getLocalBounds().width / 2)) , (display.getSize().y * .35));
        start_text.setColor(sf::Color::Black);
        start_text.setStyle(sf::Text::Bold);
        
        quit_text.setString("Quit");
        quit_text.setCharacterSize(75);
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

