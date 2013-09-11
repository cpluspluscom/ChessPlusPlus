#include "AppStateGame.hpp"

namespace chesspp
{
    AppStateGame::AppStateGame(Application *_app, sf::RenderWindow &_display)
    : AppState(_display)
    , app(_app)
    , board_config(gfx_config)
    , graphics(display, gfx_config, board_config)
    , board(board_config, {})
    {
    }

    int AppStateGame::id()
    {
        return 1;
    }

    void AppStateGame::OnRender()
    {
        graphics.drawBoard(board);
    }

    void AppStateGame::OnLButtonPressed(int x, int y) noexcept
    {
        //board->setSelected(board->getCurrent());
    }
    void AppStateGame::OnMouseMoved(int x, int y) noexcept
    {
        //board->setCurrent(x, y);
    }
    void AppStateGame::OnLButtonReleased(int x, int y) noexcept
    {
        //board->move(board->getSelected(), x, y);
        //board->setSelected(nullptr);
    }
}
