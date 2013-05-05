#ifndef GraphicsHandlerClass_HeaderPlusPlus
#define GraphicsHandlerClass_HeaderPlusPlus

#include "SFML.hpp"
#include "TextureManager.hpp"
#include "config/Configuration.hpp"
#include "board/Piece.hpp"

namespace chesspp
{
    namespace graphics
    {
        class GraphicsHandler
        {
            sf::Sprite board, pieces, validMove;
            uint16_t cell_size;
            sf::RenderWindow &display;

        public:
            GraphicsHandler(sf::RenderWindow &display);

            //Draws any sprite in the center of cell at (x, y). Assumes sprite is 80x80 as well.
            void drawSpriteAtCell(sf::Sprite &s, const int x, const int y);

            //Draws the board background.
            void drawBackground();

            //Draws a piece of p.Type and p.Suit to p.getBoardPos
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
