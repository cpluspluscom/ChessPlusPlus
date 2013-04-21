#include "King.hpp"

namespace chesspp
{
    namespace board
    {
        King::King(const Position& bPos, Color c)
            :Piece(bPos, Position(80 * 5,0), c, Type::KING)
        {
        }

        void King::addPosition(const Board* board, int x, int y)
        {
            Position pos(this->boardPos.getX() + x, this->boardPos.getY() + y);

            if (!pos.inBounds())
                return;
            if (board->hasPosition(pos) && board->at(pos)->getColor() == this->getColor())
                pos.setValid(false);
            this->trajectory.push_back(pos);

        }

        void King::makeTrajectory(const Board* board)
        {
            Log::Debug::write("KING: ");
            Log::Debug::write(this->boardPos);
            Log::Debug::writeln("makeTrajectory");

            this->trajectory.clear();

            this->addPosition(board,  0, -1);
            this->addPosition(board,  1, -1);
            this->addPosition(board,  1,  0);
            this->addPosition(board,  1,  1);
            this->addPosition(board,  0,  1);
            this->addPosition(board, -1,  1);
            this->addPosition(board, -1,  0);
            this->addPosition(board, -1,  -1);

            // At this point, Positions that are on the board and not of the same color
            // are in the trajectory.  This needs to be refined to remove check
        }
    }
}
