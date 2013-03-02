#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "SFML.hpp"
#include "TextureManager.h"
#include "board/Piece.h"
#include "board/logger.h"

#ifdef _DEBUG
#include <iostream>
using std::cout; using std::cin; using std::endl;
#endif

namespace chesspp
{
    namespace graphics
    {
        const std::string file_path = "C:/Users/Steve/Documents/Visual Studio 2012/Projects/ChessPlusPlus/";
        const int cell_size = 80; 
        const int board_width = 8;
        const int board_height = 0; //Working on a game configuration interface so these don't have to be hard coded.

        class GraphicsHandler
        {
        
        public:
            GraphicsHandler(sf::RenderWindow *_display);

            //Draws any sprite in the center of cell at (x, y). Assumes sprite is 80x80 as well.
            void drawSpriteAtCell(sf::Sprite &s, const int x, const int y);

            //Draws the board background.
            void drawBackground();

            //Draws a piece of p.Type and p.Color to p.getBoardPos
            void drawPiece(Piece *p);

            //Separate version of drawPiece to draw a piece at any location on the screen.
            void drawPieceAt(Piece *p, const sf::Vector2i &pos);

            //Draws a valid move block at cell (x,y)
            void drawValidMove(const int x, const int y);

            //Draws the entire game.
            void drawBoard(const Board *b);


        private:
            sf::Sprite board, pieces, validMove;
            std::string backgroundPath, piecePath, validMovePath;
            sf::RenderWindow *display;
        };
    }
}

#endif