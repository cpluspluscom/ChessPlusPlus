#include "Rook.hpp"

#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        static auto RookRegistration = board::Board::registerPieceClass
        (
            "Rook",
            [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s)
            -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new Rook(b, p, s, "Rook"));
            }
        );

        Rook::Rook(board::Board &b, Position_t const &pos_, Suit_t const &s_, Class_t const &pc)
        : Piece{b, pos_, s_, pc}
        {
        }

        void Rook::calcTrajectory()
        {
            //Rooks can move infinitely in the four straight directions
            using Dir = util::Direction;
            for(Dir d : {Dir::North
                        ,Dir::East
                        ,Dir::South
                        ,Dir::West})
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
