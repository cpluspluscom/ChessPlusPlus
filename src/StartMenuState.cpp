#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display) : AppState(display), app(app)
    {
        if(!menuBackgroundTexture.loadFromFile("../res/img/MainMenu.png"))
            std::cerr << "Start menu background image failed to load.\n";
        menuBackground.setTexture(menuBackgroundTexture);
    }

    void StartMenuState::onRender()
    {
        display.clear();
        display.draw(menuBackground);
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

