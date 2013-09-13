#include "ClassicFactory.hpp"

#include "board/Pawn.hpp"
#include "board/Rook.hpp"
#include "board/Knight.hpp"
#include "board/Bishop.hpp"
#include "board/King.hpp"
#include "board/Queen.hpp"

namespace chesspp
{
    namespace factory
    {
        ClassicFactory::ClassicFactory(config::BoardConfig const &bc)
        : board_config(bc)
        , cf(
        {
            {"Pawn", [&](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::mapped_type
            {
                auto d = util::Direction::East; //should not happen
                auto val = bc.metadata("pawn facing", p.y, p.x);
                if(std::string(val) == "North")
                {
                    d = util::Direction::North;
                }
                else if(std::string(val) == "South")
                {
                    d = util::Direction::South;
                }
                return board::Board::Pieces_t::mapped_type(new board::Pawn(b, p, s, d));
            }},
            {"Rook", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::mapped_type
            {
                return board::Board::Pieces_t::mapped_type(new board::Rook(b, p, s));
            }},
            {"Knight", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::mapped_type
            {
                return board::Board::Pieces_t::mapped_type(new board::Knight(b, p, s));
            }},
            {"Bishop", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::mapped_type
            {
                return board::Board::Pieces_t::mapped_type(new board::Bishop(b, p, s));
            }},
            {"King", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::mapped_type
            {
                return board::Board::Pieces_t::mapped_type(new board::King(b, p, s));
            }},
            {"Queen", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::mapped_type
            {
                return board::Board::Pieces_t::mapped_type(new board::Queen(b, p, s));
            }}
        })
        {
        }

        auto ClassicFactory::factory() const -> Factory_t const &
        {
            return cf;
        }
    }
}
