#include "ClassicFactory.hpp"

#include "piece/Pawn.hpp"
#include "piece/Rook.hpp"
#include "piece/Knight.hpp"
#include "piece/Bishop.hpp"
#include "piece/King.hpp"
#include "piece/Queen.hpp"
#ifdef CHESSPP_ENABLE_EXTRA_PIECES
#include "piece/Archer.hpp"
#endif

namespace chesspp
{
    namespace factory
    {
        ClassicFactory::ClassicFactory(config::BoardConfig const &bc)
        : board_config(bc)
        , cf(
        {
            {"Pawn", [&](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
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
                return board::Board::Pieces_t::value_type(new piece::Pawn(b, p, s, d));
            }},
            {"Rook", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new piece::Rook(b, p, s));
            }},
            {"Knight", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new piece::Knight(b, p, s));
            }},
            {"Bishop", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new piece::Bishop(b, p, s));
            }},
            {"King", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new piece::King(b, p, s));
            }},
            {"Queen", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new piece::Queen(b, p, s));
            }}
        #ifdef CHESSPP_ENABLE_EXTRA_PIECES
            ,
            {"Archer", [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s) -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new piece::Archer(b, p, s));
            }}
        #endif
        })
        {
        }

        auto ClassicFactory::factory() const -> Factory_t const &
        {
            return cf;
        }
    }
}
