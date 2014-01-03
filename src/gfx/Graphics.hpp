#ifndef ChessPlusPlus_Gfx_GraphicsHandlerClass_HeaderPlusPlus
#define ChessPlusPlus_Gfx_GraphicsHandlerClass_HeaderPlusPlus

#include "SFML.hpp"
#include "config/ResourcesConfig.hpp"
#include "config/BoardConfig.hpp"
#include "board/Board.hpp"
#include "piece/Piece.hpp"

#include <map>

namespace chesspp
{
    namespace gfx
    {
        class GraphicsHandler
        {
            sf::RenderWindow &display;
            config::ResourcesConfig &res_config;
            config::BoardConfig &board_config;
            res::ResourceManager &res;

            sf::Sprite board
            ,          valid_move
            ,          enemy_move
            ,          valid_capture
            ,          enemy_capture;

        public:
            GraphicsHandler(sf::RenderWindow &display, config::ResourcesConfig &resc, config::BoardConfig &bc);

            //Draws the board background.
            void drawBackground();

            //Draws any sprite in the center of cell at (x, y).
            void drawSpriteAtCell(sf::Sprite &s, std::size_t x, std::size_t y);

            //Draws a piece
            void drawPiece(piece::Piece const &p);

            //Separate version of drawPiece to draw a piece at any location on the screen.
            void drawPieceAt(piece::Piece const &p, sf::Vector2i const &pos);

            //draws the trajectory and captures for the piece
            void drawTrajectory(piece::Piece const &p, bool enemy = false);

            //Draws the board and pieces
            void drawBoard(board::Board const &b);
        };
    }
}

#endif
