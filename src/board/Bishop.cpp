#include "Bishop.hpp"

namespace chesspp
{
    namespace board
    {
        Bishop::Bishop(const Position& bPos, Color c)
            : Piece(bPos, Position(80 * 3,0), c, Type::BISHOP)
        {

        }

        void Bishop::makeTrajectory(const Board* board)
        {

            Log::Debug::write("BISHOP: ");
            Log::Debug::write(this->boardPos);
            Log::Debug::writeln("makeTrajectory");

            this->trajectory.clear();

            // Do the diagonals
            shootPath(board, NORTH_EAST);
            shootPath(board, SOUTH_EAST);
            shootPath(board, SOUTH_WEST);
            shootPath(board, NORTH_WEST);
        }
    }
}
