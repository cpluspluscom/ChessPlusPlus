#include "King.hpp"

#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        static auto KingRegistration = board::Board::registerPieceClass
        (
            "King",
            [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s)
            -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new King(b, p, s, "King"));
            }
        );

        King::King(board::Board &b, Position_t const &pos_, Suit_t const &s_, Class_t const &pc)
        : Piece{b, pos_, s_, pc}
        {
        }

        void King::calcTrajectory()
        {
            //Kings can move one space in all eight directions
            using Dir = util::Direction;
            for(Dir d : {Dir::North
                        ,Dir::NorthEast
                        ,Dir::East
                        ,Dir::SouthEast
                        ,Dir::South
                        ,Dir::SouthWest
                        ,Dir::West
                        ,Dir::NorthWest})
            {
                Position_t t = Position_t(pos).move(d);
                addTrajectory(t);
                addCapturing(t);
            }
        }
    }
}
