#ifndef _APPSTATEGAME_H
#define _APPSTATEGAME_H

#include "SFML.hpp"
#include "TextureManager.hpp"
#include "graphics/Graphics.hpp"
#include "config/Configuration.hpp"
#include "board/Board.hpp"

#ifdef _DEBUG
    #include <iostream>
    using std::cout; using std::cin; using std::endl;
#endif

namespace chesspp
{
    class Application;
    class AppStateGame : public AppState
    {
        Application* app;
        board::Board* board;

        graphics::GraphicsHandler graphics;
        config::BoardConfig boardConfig;

    public:
        AppStateGame(Application* _app, sf::RenderWindow *_display);
        virtual ~AppStateGame() {}

        virtual int id();
        virtual void OnRender();

        virtual void OnLButtonPressed(int x, int y);
        virtual void OnLButtonReleased(int x, int y);
        virtual void OnMouseMoved(int x, int y);
    };
}

#endif
