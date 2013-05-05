#include "Queen.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Queen::Queen(Position const &bPos, Suit c)
            :Piece(bPos, Position(80*4,0), c, Type::QUEEN)
        {

        }

        void Queen::makeTrajectory(const Board *board)
        {
            std::clog << "QUEEN: " << this->boardPos << " makeTrajectory" << std::endl;

            this->trajectory.clear();

            shootPath(board, NORTH);
            shootPath(board, NORTH_EAST);
            shootPath(board, EAST);
            shootPath(board, SOUTH_EAST);
            shootPath(board, SOUTH);
            shootPath(board, SOUTH_WEST);
            shootPath(board, WEST);
            shootPath(board, NORTH_WEST);
        }
    }
}
