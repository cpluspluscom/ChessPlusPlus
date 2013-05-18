#include "Queen.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace board
    {
        Queen::Queen(Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
        {
        }

        void Queen::calcTrajectory()
        {
            std::clog << "Queen@" << pos << "->calcTrajectory()" << std::endl;

            //Queens can move infinitely in all eight directions

            for(Direction d : {Direction::North
                              ,Direction::NorthEast
                              ,Direction::East
                              ,Direction::SouthEast
                              ,Direction::South
                              ,Direction::SouthWest
                              ,Direction::West
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

        Queen::moveAnimation(Position_t const &from, Position_t const &to)
        {
            //
        }
    }
}
