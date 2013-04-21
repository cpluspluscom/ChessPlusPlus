#include "Knight.hpp"

namespace chesspp
{
    namespace board
    {
        Knight::Knight(const Position& bPos, Color c)
            :Piece(bPos, Position(80 * 2,0), c, Type::KNIGHT)
        {

        }

        void Knight::makeTrajectory(const Board* board)
        {
            Log::Debug::write("KNIGHT: ");
            Log::Debug::write(this->boardPos);
            Log::Debug::writeln("makeTrajectory");

            this->trajectory.clear();

            addPosition(board,  1, -2 );
            addPosition(board,  2, -1 );
            addPosition(board,  2,  1 );
            addPosition(board,  1,  2 );
            addPosition(board, -1,  2 );
            addPosition(board, -2,  1 );
            addPosition(board, -2, -1 );
            addPosition(board, -1, -2 );
        }

        void Knight::addPosition(const Board* board, int x, int y)
        {
            Position pos(this->boardPos.getX() + x, this->boardPos.getY() + y);

            if (!pos.inBounds())
                return;
            if (board->hasPosition(pos) && board->at(pos)->getColor() == this->getColor())
                pos.setValid(false);
            this->trajectory.push_back(pos);

        }
    }
}
