#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display) : AppState(display), app(app)
    {
        if(!menuBackgroundTexture.loadFromFile("../res/img/MainMenuBackground.png"))
            std::cerr << "Start menu background image failed to load." << std::endl;
        else menuBackground.setTexture(menuBackgroundTexture);
            
            
        if(!logoTexture.loadFromFile("../res/img/Logo.png"))
            std::cerr << "Logo failed to load." << std::endl;
        else
        {
            logo.setTexture(logoTexture, true);
            //Sets position at centered horizontally, down 10% vertically;
            logo.setPosition(((display.getSize().x / 2) - (logo.getLocalBounds().width / 2)) , display.getSize().y * .10);
        }
    }

    void StartMenuState::onRender()
    {
        display.clear();
        display.draw(menuBackground);
        display.draw(logo);
        display.display();
    }

    void StartMenuState::onLButtonReleased(int x, int y)
    {
        /** If clicked on Start button **/
        if((x >= 250 && x <= 400) && (y >= 250 && y <= 300))
        {
            std::clog << "State changing to ChessPlusPlus." << std::endl;
            app.changeState<chesspp::ChessPlusPlusState>(std::ref(app), std::ref(display));
        }
        
        /** If clicked on Exit button **/
        if((x >= 270 && x <= 390) && (y >= 330 && y <= 385))
        {
            std::clog << "Exiting from StartMenuState." << std::endl;
            app.setRunning(false);
        }
    }
    
}

