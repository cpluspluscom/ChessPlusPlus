#include "Bishop.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace board
    {
        Bishop::Bishop(Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
        {
        }

        void Bishop::calcTrajectory()
        {
            std::clog << "Bishop@" << pos << "->calcTrajectory()" << std::endl;

            //Bishops can move infinitely in the four diagonal directions

            for(Direction d : {Direction::NorthEast
                              ,Direction::SouthEast
                              ,Direction::SouthWest
                              ,Direction::NorthWest})
            {
                Position_t t;
                for(signed i = 0; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addTrajectory(t);
                    addCapturing(t);
                }
            }
        }

        Bishop::moveAnimation(Position_t const &from, Position_t const &to)
        {
            //
        }
    }
}
