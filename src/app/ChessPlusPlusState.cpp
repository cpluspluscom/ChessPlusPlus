#include "ChessPlusPlusState.hpp"

#include "StartMenuState.hpp"
#include "util/Utilities.hpp"

#include <iostream>
#include <algorithm>

namespace chesspp
{
    namespace app
    {
        ChessPlusPlusState::ChessPlusPlusState(Application &app_, sf::RenderWindow &disp)
        : AppState(disp)                    //can't use {}
        , app(app_)                         //can't use {}
        , res_config(app.resourcesConfig()) //can't use {}
        , board_config{res_config}
        , graphics{display, res_config, board_config}
        , board{board_config}
        , players{util::KeyIter<config::BoardConfig::Textures_t>
                               (board_config.texturePaths().cbegin()),
                  util::KeyIter<config::BoardConfig::Textures_t>
                               (board_config.texturePaths().cend())}
        , turn{players.find(board_config.metadata("first turn"))}
        {
            std::clog << "Number of players: " << players.size() << std::endl;
            if(turn == players.end())
            {
                turn = players.begin();
            }
        }

        void ChessPlusPlusState::nextTurn()
        {
            if(++turn == players.end())
            {
                turn = players.begin();
            }
        }

        board::Board::Pieces_t::iterator ChessPlusPlusState::find(board::Board::Position_t const &pos) const
        {
            return std::find_if(board.begin(), board.end(),
            [&](std::unique_ptr<piece::Piece> const &up) -> bool
            {
                return up->pos == pos;
            });
        }

        void ChessPlusPlusState::onRender()
        {
            graphics.drawBoard(board);
            if(selected != board.end())
            {
                graphics.drawTrajectory(**selected);
            }
            if(board.valid(p))
            {
                auto piece = find(p);
                if(piece != board.end())
                {
                    graphics.drawTrajectory(**piece, (*piece)->suit != *turn);
                }
            }
        }

        void ChessPlusPlusState::onKeyPressed(sf::Keyboard::Key key, bool /*alt*/, bool /*control*/, bool /*shift*/, bool /*system*/)
        {
            if(key == sf::Keyboard::Escape)
            { //Exit to menu screen
                return app.changeState<StartMenuState>(std::ref(app), std::ref(display));
            }
        }
        void ChessPlusPlusState::onMouseMoved(int x, int y)
        {
            p.x = static_cast<board::Board::Position_t::value_type>(x/board.config.cellWidth());
            p.y = static_cast<board::Board::Position_t::value_type>(y/board.config.cellHeight());
        }
        void ChessPlusPlusState::onLButtonPressed(int x, int y)
        {
        }
        void ChessPlusPlusState::onLButtonReleased(int x, int y)
        {
            if(!board.valid(p)) return;
            if(selected == board.end())
            {
                selected = find(p); //doesn't matter if board.end(), selected won't change then
                if(selected != board.end() && (*selected)->suit != *turn)
                {
                    selected = board.end(); //can't select enemy pieces
                }
            }
            else
            {
                if(find(p) == board.end() || (*find(p))->suit != (*selected)->suit)[&]
                {
                    {
                        auto it = std::find_if(board.pieceCapturings().begin(),
                                               board.pieceCapturings().end(),
                                               [&](board::Board::Movements_t::value_type const &m)
                                               {
                                                   return m.first == selected && m.second == p;
                                               });
                        if(it != board.pieceCapturings().end())
                        {
                            for(auto jt = board.pieceCapturables().begin(); jt != board.pieceCapturables().end(); ++jt)
                            {
                                if(jt->second == p)
                                {
                                    if(board.capture(selected, it, jt))
                                    {
                                        nextTurn();
                                        return;
                                    }
                                }
                            }
                        }
                    }
                    {
                        auto it = std::find_if(board.pieceTrajectories().begin(),
                                               board.pieceTrajectories().end(),
                                               [&](board::Board::Movements_t::value_type const &m)
                                               {
                                                   return m.first == selected && m.second == p;
                                               });
                        if(it != board.pieceTrajectories().end())
                        {
                            if(board.move(selected, it))
                            {
                                nextTurn();
                            }
                        }
                    }
                }();
                selected = board.end(); //deselect
            }
        }
    }
}
