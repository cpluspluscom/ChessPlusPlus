#ifndef ChessPlusPlusGameStateClass_HeaderPlusPlus
#define ChessPlusPlusGameStateClass_HeaderPlusPlus

#include "SFML.hpp"
#include "gfx/Graphics.hpp"
#include "board/Board.hpp"

#include "AppState.hpp"
#include "Application.hpp"

#include <set>

namespace chesspp
{
    namespace app
    {
        class ChessPlusPlusState : public AppState
        {
            Application &app;
            config::ResourcesConfig &res_config;
            config::BoardConfig board_config;
            gfx::GraphicsHandler graphics;
            board::Board board;

            board::Board::Pieces_t::iterator selected = board.end();
            board::Board::Position_t p;
            using Players_t = std::set<board::Board::Suit>;
            Players_t players;
            Players_t::const_iterator turn;
            void nextTurn();
            board::Board::Pieces_t::iterator find(board::Board::Position_t const &pos) const;

        public:
            ChessPlusPlusState(Application &app, sf::RenderWindow &display);
            virtual ~ChessPlusPlusState() = default;

            virtual void onRender() override;

            virtual void onMouseMoved(int x, int y) override;
            virtual void onLButtonPressed(int x, int y) override;
            virtual void onLButtonReleased(int x, int y) override;
        };
    }
}

#endif
