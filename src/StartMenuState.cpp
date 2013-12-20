#include "StartMenuState.hpp"

namespace chesspp
{
    StartMenuState::StartMenuState(Application &app, sf::RenderWindow &display) : AppState(display), app(app)
    {
        if(!menuBackgroundTexture.loadFromFile("../res/img/start_menu_placeholder.jpg"))
            std::cerr << "Start menu background image failed to load.\n";
        menuBackground.setTexture(menuBackgroundTexture);
    }

    void StartMenuState::onRender()
    {
        //display.clear();
        display.draw(menuBackground);
        display.display();
    }

    void StartMenuState::onLButtonPressed(int x, int y)
    {
        
    }
}

