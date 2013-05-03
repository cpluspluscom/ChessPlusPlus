#include "Knight.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Knight::Knight(Position const &bPos, Color c)
        : Piece(bPos, Position(80*2, 0), c, Type::KNIGHT)
        {

        }

        void Knight::makeTrajectory(Board const *board)
        {
            std::clog << "KNIGHT: " << this->boardPos << " makeTrajectory" << std::endl;

            this->trajectory.clear();

            addPosition(board,  1, -2);
            addPosition(board,  2, -1);
            addPosition(board,  2,  1);
            addPosition(board,  1,  2);
            addPosition(board, -1,  2);
            addPosition(board, -2,  1);
            addPosition(board, -2, -1);
            addPosition(board, -1, -2);
        }

        void Knight::addPosition(Board const *board, int x, int y)
        {
            Position pos(this->boardPos.getX() + x, this->boardPos.getY() + y);

            if (!pos.inBounds())
                return;
            if (board->hasPosition(pos) &&board->at(pos)->getColor() == this->getColor())
                pos.setValid(false);
            this->trajectory.push_back(pos);

        }
    }
}
