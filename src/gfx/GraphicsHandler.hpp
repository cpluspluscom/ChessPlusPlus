#ifndef chesspp_gfx_GraphicsHandler_HeaderPlusPlus
#define chesspp_gfx_GraphicsHandler_HeaderPlusPlus

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
        /**
         * \brief
         * Handles drawing graphics, such as pieces, trajectories, and boards.
         */
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
            /**
             * \brief
             * Constructs for a specific sf::RenderWindow given the resource and board
             * configurations.
             * 
             * \param display The sf::RenderWindow, must outlive this instance.
             * \param resc The chesspp::config::ResourcesConfig, must outlive this instance.
             * \param bc The chesspp::config::BoardConfig, must outlive this instance.
             */
            GraphicsHandler(sf::RenderWindow &display, config::ResourcesConfig &resc, config::BoardConfig &bc);

            /**
             * \brief
             * Draws the board background.
             */
            void drawBackground();

            /**
             * \brief
             * Draws any sprite in the center of cell at (x, y).
             * 
             * \param s The sprite to draw, centered on (x, y). Changes the sprite's position.
             */
            void drawSpriteAtCell(sf::Sprite &s, std::size_t x, std::size_t y);

            /**
             * \brief
             * Draws a piece at its real location.
             * 
             * \param p The piece to draw.
             */
            void drawPiece(piece::Piece const &p);

            /**
             * \brief
             * Draws a piece at a different location than it actually is.
             * 
             * \param p The piece to draw.
             * \param pos The location to draw the piece at.
             */
            void drawPieceAt(piece::Piece const &p, sf::Vector2i const &pos);

            /**
             * \brief
             * Draws a piece's trajectory moves and capturing moves.
             * 
             * \param p The piece for which to draw trajectory and capturings.
             * \param enemy true if the piece is an enemy piece, false otherwise.
             */
            void drawTrajectory(piece::Piece const &p, bool enemy = false);

            /**
             * \brief
             * Draws a board and its pieces.
             * 
             * \param b The board to draw.
             */
            void drawBoard(board::Board const &b);
        };
    }
}

#endif
