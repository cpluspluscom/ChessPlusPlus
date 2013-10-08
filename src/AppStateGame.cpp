#include "AppStateGame.hpp"

#include "util/Utilities.hpp"

#include <iostream>

namespace chesspp
{
    AppStateGame::AppStateGame(Application *_app, sf::RenderWindow &_display)
    : AppState(_display)
    , app(_app)
    , board_config(gfx_config)
    , classic_factory(board_config)
    , graphics(display, gfx_config, board_config)
    , board(board_config, classic_factory.factory())
    , players(util::KeyIter<config::BoardConfig::Textures_t>
                           (board_config.texturePaths().cbegin()),
              util::KeyIter<config::BoardConfig::Textures_t>
                           (board_config.texturePaths().cend()))
    , turn(players.find(board_config.metadata("first turn")))
    {
        std::clog << "Number of players: " << players.size() << std::endl;
        if(turn == players.end())
        {
            turn = players.begin();
        }
    }

    void AppStateGame::nextTurn()
    {
        if(++turn == players.end())
        {
            turn = players.begin();
        }
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
                graphics.drawTrajectory(*piece, piece->suit != *turn);
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
            if(selected != nullptr && selected->suit != *turn)
            {
                selected = nullptr; //can't select enemy pieces
            }
        }
        else
        {
            [&]
            {
                if(selected->captures.find(p) != selected->captures.end())
                {
                    for(auto it = board.Captures().cbegin(); it != board.Captures().cend(); ++it)
                    {
                        if(it->second == p)
                        {
                            board.capture(selected->pos, it);
                            nextTurn();
                            return;
                        }
                    }
                }
                if(selected->trajectory.find(p) != selected->trajectory.end())
                {
                    board.move(selected->pos, p);
                    nextTurn();
                }
            }();
            selected = nullptr; //deselect
        }
    }
}
