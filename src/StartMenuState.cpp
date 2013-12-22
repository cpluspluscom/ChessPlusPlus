#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display) : AppState(display), app(app)
    {
        if(!menuBackgroundTexture.loadFromFile("../res/img/chessboard_640x640.png"))
            std::cerr << "Start menu background image failed to load.\n";
        menuBackground.setTexture(menuBackgroundTexture);
    }

    void StartMenuState::onRender()
    {
        display.clear();
        display.draw(menuBackground);
        display.display();
    }

    void StartMenuState::onLButtonPressed(int x, int y)
    {
        destState = AppState::States::CHESSPLUSPLUSSTATE;
        std::clog << "destState changing to: " << static_cast<int>(destState) << std::endl;
    }
    
}

