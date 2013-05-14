#include "Rook.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Rook::Rook(Position const &bPos, Color c)
        : Piece(bPos, Position(80*1, 0), c, Type::ROOK)
        {

        }
        void Rook::makeTrajectory(Board const *board)
        {
            std::clog << "ROOK: " << this->boardPos << " makeTrajectory" << std::endl;

            this->trajectory.clear();

            shootPath(board, NORTH);
            shootPath(board, EAST);
            shootPath(board, SOUTH);
            shootPath(board, WEST);
        }
    }
}
