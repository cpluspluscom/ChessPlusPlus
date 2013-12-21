#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display) : AppState(display), app(app)
    {
        if(!menuBackgroundTexture.loadFromFile("../res/img/chessboard_640x640.png"))
            std::cerr << "Start menu background image failed to load.\n";
        menuBackground.setTexture(menuBackgroundTexture);
        
        destState = AppState::States::CURRENTSTATE;
    }

    void StartMenuState::onRender()
    {
        display.clear();
        display.draw(menuBackground);
        display.display();
    }

    void StartMenuState::onLButtonPressed(int x, int y)
    {
        //destState = AppState::States::CHESSPLUSPLUSSTATE;
    }
    
}

