#include "Bishop.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Bishop::Bishop(Position const &bPos, Color c)
        : Piece(bPos, Position(80*3, 0), c, Type::BISHOP)
        {
        }

        void Bishop::makeTrajectory(Board const *board)
        {
            std::clog << "BISHOP: " << this->boardPos << " makeTrajectory" << std::endl;

            this->trajectory.clear();

            // Do the diagonals
            shootPath(board, NORTH_EAST);
            shootPath(board, SOUTH_EAST);
            shootPath(board, SOUTH_WEST);
            shootPath(board, NORTH_WEST);
        }
    }
}
