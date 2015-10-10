#include "Queen.hpp"

#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        static auto QueenRegistration = board::Board::registerPieceClass
        (
            "Queen",
            [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s)
            -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new Queen(b, p, s, "Queen"));
            }
        );

        Queen::Queen(board::Board &b, Position_t const &pos_, Suit_t const &s_, Class_t const &pc)
        : Piece{b, pos_, s_, pc}
        {
        }

        void Queen::calcTrajectory()
        {
            //Queens can move infinitely in all eight directions
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
                Position_t t;
                for(signed i = 1; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addCapturing(t);
                    if(!board.occupied(t))
                    {
                        addTrajectory(t);
                    }
                    else break; //can't jump over pieces
                }
            }
        }
    }
}
