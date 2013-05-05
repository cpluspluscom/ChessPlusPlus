#ifndef GameApllicationStateClass_HeaderPlusPlus
#define GameApllicationStateClass_HeaderPlusPlus

#include "SFML.hpp"
#include "TextureManager.hpp"
#include "gfx/Graphics.hpp"
#include "config/Configuration.hpp"
#include "board/Board.hpp"

#include "AppState.hpp"

namespace chesspp
{
    class Application;
    class AppStateGame : public AppState
    {
        Application *app;
        board::Board board;

        graphics::GraphicsHandler graphics;
        config::BoardConfig boardConfig;

    public:
        AppStateGame(Application *app, sf::RenderWindow *display);
        virtual ~AppStateGame() noexcept = default;

        virtual int id();
        virtual void OnRender();

        virtual void OnLButtonPressed(int x, int y) noexcept;
        virtual void OnLButtonReleased(int x, int y) noexcept;
        virtual void OnMouseMoved(int x, int y) noexcept;
    };
}

#endif
