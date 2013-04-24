#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "SFML.hpp"
#include "TextureManager.hpp"
#include "config/Configuration.hpp"
#include "board/Piece.hpp"
#include "log/Logger.hpp"

#ifdef _DEBUG
#include <iostream>
using std::cout; using std::cin; using std::endl;
#endif

namespace chesspp
{
    namespace graphics
    {
        class GraphicsHandler
        {
            sf::Sprite board, pieces, validMove;
            uint16_t cell_size;
            sf::RenderWindow *display;

        public:
            GraphicsHandler(sf::RenderWindow *_display);

            //Draws any sprite in the center of cell at (x, y). Assumes sprite is 80x80 as well.
            void drawSpriteAtCell(sf::Sprite &s, const int x, const int y);

            //Draws the board background.
            void drawBackground();

            //Draws a piece of p.Type and p.Color to p.getBoardPos
            void drawPiece(board::Piece *p);

            //Separate version of drawPiece to draw a piece at any location on the screen.
            void drawPieceAt(board::Piece *p, const sf::Vector2i &pos);

            //Draws a valid move block at cell (x,y)
            void drawValidMove(const int x, const int y);

            //Draws the entire game.
            void drawBoard(const board::Board *b);
        };
    }
}

#endif
