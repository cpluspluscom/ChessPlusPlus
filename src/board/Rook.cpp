#include "Rook.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace board
    {
        Rook::Rook(Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
		, castling(b.getInteraction<Castling>())
        {
			//not yet moved, can castle
			castling.addFast(this);
        }

        void Rook::calcTrajectory()
        {
            std::clog << "Rook@" << pos << "->calcTrajectory()" << std::endl;

            //Rooks can move infinitely in the four straight directions

            for(Direction d : {Direction::North
                              ,Direction::East
                              ,Direction::South
                              ,Direction::West})
            {
                Position_t t;
                for(signed i = 0; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addTrajectory(t);
                    addCapturing(t);
                }
            }
        }

		void Rook::moveUpdate(Position_t const &from, Position_t const &to)
		{
			//moved, can no longer castle
			castling.removeFast(this);
		}
    }
}
