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
        {
            board = sf::Sprite(TextureManager::getInstance().Load(gfx_config.spritePath("board", "board")));
            /**/pieces = sf::Sprite(TextureManager::getInstance().Load(gfx_config.spritePath("board", "pieces")));
            validMove = sf::Sprite(TextureManager::getInstance().Load(gfx_config.spritePath("board", "valid move")));
        }

        void GraphicsHandler::drawSpriteAtCell(sf::Sprite &s, int x, int y)
        {
            s.setPosition(x*board_config.cellWidth(), y*board_config.cellHeight());
            display.draw(s);
        }
        void GraphicsHandler::drawBackground()
        {
            display.draw(board);
        }
        void GraphicsHandler::drawPiece(board::Piece &p)
        {
            //pieces.setTexture
            drawSpriteAtCell(pieces, p.pos.x, p.pos.y);
        }
        void GraphicsHandler::drawPieceAt(board::Piece &p, const sf::Vector2i &pos)
        {
            //pieces.setTexture
            pieces.setPosition(pos.x - (board_config.cellWidth() / 2), pos.y - (board_config.cellHeight() / 2));

            display.draw(pieces);
        }
        void GraphicsHandler::drawValidMove(int x, int y)
        {
            drawSpriteAtCell(validMove, x, y);
        }
        void GraphicsHandler::drawBoard(board::Board const &b)
        {
            drawBackground();

            //Valid moves are drawn for the piece being hovered over
            //Or the piece that is currently selected
            board::Piece *pCurrent = /*b.getCurrent()*/nullptr;
            board::Piece *pSelect  = /*b.getSelected()*/nullptr;
            if(pSelect)
            {
                for(auto &i: pSelect->trajectory)
                {
                    drawValidMove(i.x, i.y);
                }
            }
            else if(pCurrent)
            {
                for(auto &i: pCurrent->trajectory)
                {
                    drawValidMove(i.x, i.y);
                }
            }

            //Draw the non-selected pieces
            //for(auto &i: b.pieces)
            {
                //if(i /*&& i != b.getSelected()*/)
                {
                    //drawPiece(i);
                }
            }

            //Draw the selected piece
            //if(b.getSelected())
            {
                //drawPieceAt(b->getSelected(), sf::Mouse::getPosition(*display));
            }
        }
    }
}
