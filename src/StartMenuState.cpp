#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display) : AppState(display), app(app)
    {
        // Load and initialize resources
        menuBackground.setTexture(TextureManager::instance().load(gfx_config.spritePath("menu", "background")));
        logo.setTexture(TextureManager::instance().load(gfx_config.spritePath("logo")), true);
        
        // Sets position at centered horizontally, down 10% vertically
        logo.setPosition(((display.getSize().x / 2) - (logo.getLocalBounds().width / 2)) , (display.getSize().y * .10));
        
        if(!font.loadFromFile("../res/fonts/FreeMono.ttf"))
        {
            std::cerr << "Font failed to load." << std::endl;
        }
        else
        {
            startText.setFont(font);
            quitText.setFont(font);
        }
        
        // Initialize text
        startText.setString("Start");
        startText.setCharacterSize(75);
        startText.setPosition(((display.getSize().x / 2) - (startText.getLocalBounds().width / 2)) , (display.getSize().y * .35));
        startText.setColor(sf::Color::Black);
        startText.setStyle(sf::Text::Bold);
        
        quitText.setString("Quit");
        quitText.setCharacterSize(75);
        quitText.setPosition(((display.getSize().x / 2) - (quitText.getLocalBounds().width / 2)) , (display.getSize().y * .47));
        quitText.setColor(sf::Color::Black);
        quitText.setStyle(sf::Text::Bold);
    }

    void StartMenuState::onRender()
    {
        display.clear();
        display.draw(menuBackground);
        display.draw(logo);
        display.draw(startText);
        display.draw(quitText);
        display.display();
    }

    void StartMenuState::onLButtonReleased(int x, int y)
    {
        // If clicked on Start button
        if(startText.getGlobalBounds().contains(x,y))
        {
            std::clog << "State changing to ChessPlusPlus." << std::endl;
            app.changeState<chesspp::ChessPlusPlusState>(std::ref(app), std::ref(display));
        }
        
        // If clicked on Exit button
        if(quitText.getGlobalBounds().contains(x,y))
        {
            std::clog << "Exiting from StartMenuState." << std::endl;
            app.stop();
        }
    }
    
}

