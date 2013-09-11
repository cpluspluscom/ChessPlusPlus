#ifndef GameApllicationStateClass_HeaderPlusPlus
#define GameApllicationStateClass_HeaderPlusPlus

#include "SFML.hpp"
#include "TextureManager.hpp"
#include "gfx/Graphics.hpp"
#include "config/Configuration.hpp"
#include "config/GraphicsConfig.hpp"
#include "board/Board.hpp"

#include "AppState.hpp"

namespace chesspp
{
    class Application;
    class AppStateGame : public AppState
    {
        config::GraphicsConfig gfx_config;
        gfx::GraphicsHandler graphics;
        config::BoardConfig board_config;
        Application *app;
        board::Board board;

    public:
        AppStateGame(Application *app, sf::RenderWindow &display);
        virtual ~AppStateGame() = default;

        virtual int id();
        virtual void OnRender();

        virtual void OnLButtonPressed(int x, int y) noexcept;
        virtual void OnLButtonReleased(int x, int y) noexcept;
        virtual void OnMouseMoved(int x, int y) noexcept;
    };
}

#endif
