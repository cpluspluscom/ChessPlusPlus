#include "Queen.hpp"

namespace chesspp
{
    namespace board
    {
        Queen::Queen(const Position& bPos, Color c)
            :Piece(bPos, Position(80 * 4,0), c, Type::QUEEN)
        {

        }

        void Queen::makeTrajectory(const Board* board)
        {
            Log::Debug::write("QUEEN: ");
            Log::Debug::write(this->boardPos);
            Log::Debug::writeln("makeTrajectory");

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
