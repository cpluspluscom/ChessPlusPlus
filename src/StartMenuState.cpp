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

    void StartMenuState::onLButtonPressed(int x, int y)
    {
        std::clog << "State changing to ChessPlusPlus." << std::endl;
        app.changeState<chesspp::ChessPlusPlusState>(std::ref(app), std::ref(display));
    }
    
}

