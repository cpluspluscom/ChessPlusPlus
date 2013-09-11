#include "AppStateGame.hpp"

namespace chesspp
{
    AppStateGame::AppStateGame(Application *_app, sf::RenderWindow &_display)
    : AppState(_display)
    , app(_app)
    , board_config(gfx_config)
    , graphics(display, gfx_config, board_config)
    , board(board_config, {/**/})
    {
    }

    void AppStateGame::OnRender()
    {
        graphics.drawBoard(board);
        if(selected != nullptr)
        {
            graphics.drawTrajectory(*selected);
        }
        if(board.valid(p))
        {
            auto piece = board.at(p);
            if(piece != nullptr)
            {
                graphics.drawTrajectory(*piece, piece->suit == /**/"White");
            }
        }
    }

    void AppStateGame::OnMouseMoved(int x, int y) noexcept
    {
        p.x = static_cast<board::Board::Position_t::value_type>(x/board.config.cellWidth());
        p.y = static_cast<board::Board::Position_t::value_type>(y/board.config.cellHeight());
    }
    void AppStateGame::OnLButtonPressed(int x, int y) noexcept
    {
    }
    void AppStateGame::OnLButtonReleased(int x, int y) noexcept
    {
        if(!board.valid(p)) return;
        if(selected == nullptr)
        {
            selected = board.at(p); //doesn't matter if nullptr, selected won't change then
        }
        else
        {
            if(selected->trajectory.find(p) != selected->trajectory.end())
            {
                //
            }
            else if(selected->captures.find(p) != selected->captures.end())
            {
                //
            }
        }
    }
}
