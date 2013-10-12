#include "Graphics.hpp"

#include "TextureManager.hpp"
#include "config/Configuration.hpp"

#include <iostream>

namespace chesspp
{
    namespace gfx
    {
        GraphicsHandler::GraphicsHandler(sf::RenderWindow &disp, config::GraphicsConfig &gfxc, config::BoardConfig &bc)
        : display(disp)
        , gfx_config(gfxc)
        , board_config(bc)
        , board        (TextureManager::instance().load(gfx_config.spritePath("board", "board"        )))
        , valid_move   (TextureManager::instance().load(gfx_config.spritePath("board", "valid move"   )))
        , enemy_move   (TextureManager::instance().load(gfx_config.spritePath("board", "enemy move"   )))
        , valid_capture(TextureManager::instance().load(gfx_config.spritePath("board", "valid capture")))
        , enemy_capture(TextureManager::instance().load(gfx_config.spritePath("board", "enemy capture")))
        {
        }

        void GraphicsHandler::drawBackground()
        {
            display.draw(board);
        }
        void GraphicsHandler::drawSpriteAtCell(sf::Sprite &s, std::size_t x, std::size_t y)
        {
            s.setPosition(x*board_config.cellWidth(), y*board_config.cellHeight());
            display.draw(s);
        }
        void GraphicsHandler::drawPiece(board::Piece const &p)
        {
            sf::Sprite piece {TextureManager::instance().load(p.texture())};
            drawSpriteAtCell(piece, p.pos.x, p.pos.y);
        }
        void GraphicsHandler::drawPieceAt(board::Piece const &p, sf::Vector2i const &pos)
        {
            sf::Sprite piece {TextureManager::instance().load(p.texture())};
            piece.setPosition(pos.x - (board_config.cellWidth()/2), pos.y - (board_config.cellHeight()/2));
            display.draw(piece);
        }
        void GraphicsHandler::drawTrajectory(board::Piece const &p, bool enemy)
        {
            {
                auto &sprite = (enemy? enemy_move : valid_move);
                for(auto const &it : p.board.pieceTrajectory(p))
                {
                    if(!p.board.occupied(it.second))
                    {
                        if(std::find_if(p.board.pieceCapturables().begin(),
                                        p.board.pieceCapturables().end(),
                                        [&](board::Board::Movements_t::value_type const &m)
                                        {
                                            return m.second == it.second && (*m.first)->suit != p.suit;
                                        }) == p.board.pieceCapturables().end())
                        {
                            drawSpriteAtCell(sprite, it.second.x, it.second.y);
                        }
                    }
                }
            }
            {
                auto &sprite = (enemy? enemy_capture : valid_capture);
                for(auto const &it : p.board.pieceCapturing(p))
                {
                    for(auto const &c : p.board.pieceCapturables())
                    {
                        if(c.second == it.second && (*c.first)->suit != p.suit)
                        {
                            drawSpriteAtCell(sprite, it.second.x, it.second.y);
                            auto jt = std::find_if(p.board.pieceTrajectories().begin(),
                                                   p.board.pieceTrajectories().end(),
                                                   [&](board::Board::Movements_t::value_type const &m)
                                                   {
                                                       return (*m.first)->pos == it.second;
                                                   });
                            if(jt != p.board.pieceTrajectories().end())
                            {
                                drawPiece(**(jt->first)); //redraw
                            }
                            break;
                        }
                    }
                }
            }
        }
        void GraphicsHandler::drawBoard(board::Board const &b)
        {
            drawBackground();

            for(auto const &pp : b)
            {
                drawPiece(*pp);
            }
        }
    }
}
