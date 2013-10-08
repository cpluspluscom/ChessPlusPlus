#include "Graphics.hpp"

#include "TextureManager.hpp"
#include "config/Configuration.hpp"

#include <iostream>

namespace chesspp
{
    namespace gfx
    {
        GraphicsHandler::GraphicsHandler(sf::RenderWindow &display, config::GraphicsConfig &gfxc, config::BoardConfig &bc)
        : display(display)
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
                for(auto const &pos : p.trajectory)
                {
                    if(p.board.at(pos) == nullptr)
                    {
                        bool capturable = false;
                        for(auto const &c : p.board.Captures())
                        {
                            if(c.second == pos && c.first->second->suit != p.suit)
                            {
                                capturable = true;
                                break;
                            }
                        }
                        if(!capturable)
                        {
                            drawSpriteAtCell(sprite, pos.x, pos.y);
                        }
                    }
                }
            }
            {
                auto &sprite = (enemy? enemy_capture : valid_capture);
                for(auto const &pos : p.captures)
                {
                    auto piece = p.board.at(pos);
                    for(auto const &c : p.board.Captures())
                    {
                        if(c.second == pos && c.first->second->suit != p.suit)
                        {
                            drawSpriteAtCell(sprite, pos.x, pos.y);
                            if(piece != nullptr)
                            {
                                drawPiece(*piece); //redraw
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
                drawPiece(*pp.second);
            }
        }
    }
}
