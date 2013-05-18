#include "Knight.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace board
    {
        Knight::Knight(Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
        {

        }

        void Knight::calcTrajectory()
        {
            std::clog << "Knight@" << pos << "->calcTrajectory()" << std::endl;

            //Knights can only move in 3-long 2-short L shapes

            for(Position_t p : {Position_t( 1, -2)
                               ,Position_t( 2, -1)
                               ,Position_t( 2,  1)
                               ,Position_t( 1,  2)
                               ,Position_t(-1,  2)
                               ,Position_t(-2,  1)
                               ,Position_t(-2, -1)
                               ,Position_t(-1, -2)})
            {
                Position_t t = Position_t(pos).move(p.x, p.y);
                addTrajectory(t);
                addCapturing(t);
            }
        }

        King::moveAnimation(Position_t const &from, Position_t const &to)
        {
            //
        }
    }
}
