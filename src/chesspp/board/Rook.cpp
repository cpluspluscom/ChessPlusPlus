#include "Rook.hpp"

namespace chesspp
{
    namespace board
    {
        Rook::Rook(const Position& bPos, Color c)
            :Piece(bPos, Position(80 * 1,0), c, Type::ROOK)
        {

        }
        void Rook::makeTrajectory(const Board* board)
        {
            Log::Debug::write("ROOK: ");
            Log::Debug::write(this->boardPos);
            Log::Debug::writeln("makeTrajectory");

            this->trajectory.clear();

            shootPath(board, NORTH);
            shootPath(board, EAST);
            shootPath(board, SOUTH);
            shootPath(board, WEST);
        }
    }
}
