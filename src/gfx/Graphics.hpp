#ifndef GraphicsHandlerClass_HeaderPlusPlus
#define GraphicsHandlerClass_HeaderPlusPlus

#include "SFML.hpp"
#include "board/Board.hpp"

namespace chesspp
{
    namespace gfx
    {
        class GraphicsHandler
        {
            sf::Sprite board, pieces, validMove;
            sf::RenderWindow &display;
			config::GraphicsConfig &gfx_config;
			config::BoardConfig &board_config;

        public:
            GraphicsHandler(sf::RenderWindow &display, config::GraphicsConfig &gfxc, config::BoardConfig &bc);

            //Draws any sprite in the center of cell at (x, y).
            void drawSpriteAtCell(sf::Sprite &s, int x, int y);

            //Draws the board background.
            void drawBackground();

            //Draws a piece
            void drawPiece(board::Piece &p);

            //Separate version of drawPiece to draw a piece at any location on the screen.
            void drawPieceAt(board::Piece &p, const sf::Vector2i &pos);

            //Draws a valid move block at cell (x,y)
            void drawValidMove(int x, int y);

            //Draws the entire game.
            void drawBoard(board::Board const &b);
        };
    }
}

#endif
