#include "Pawn.hpp"

namespace chesspp
{
    namespace board
    {
        Pawn::Pawn(const Position& bPos, Color c)
            :Piece(bPos, Position(0,0), c, Type::PAWN), firstMove(true)
        {
        }

        // Other pieces can be more automatic
        void Pawn::makeTrajectory(const Board* board)
        {
            Log::Debug::write("PAWN: ");
            Log::Debug::write(this->boardPos);
            Log::Debug::writeln("makeTrajectory");

            // Clear the old trajectory
            trajectory.clear();

            // Figure out if going up or down
            int offset = this->getColor() == BLACK ? 1 : -1;

            // Set pos to left diagonal
            Position pos(this->getBoardPos().getX() - 1, this->getBoardPos().getY() + offset);
            if (pos.inBounds())
            {
                if (!board->hasPosition(pos) || board->at(pos)->getColor() == this->getColor())
                    pos.setValid(false);
                trajectory.push_back(pos);
            }

            // Reset validity and move right (straight ahead)
            pos.setValid(true);
            pos.move(EAST);

            if (pos.inBounds()) // Which happens, it is be a different piece otherwise
            {
                if (board->hasPosition(pos))
                    pos.setValid(false);

                trajectory.push_back(pos);
            }

            // We keep the validity from before to check the position ahead
            if (firstMove)
            {
                pos.move(0, offset);         // Move Foward
                if (board->hasPosition(pos))
                    pos.setValid(false);

                trajectory.push_back(pos);
                pos.move(0, -offset);        // Move Back, as if nothing happened :)
            }

            // Move to the right again, the other diagonal
            pos.move(EAST);
            pos.setValid(true);
            if (pos.inBounds())
            {
                if (!board->hasPosition(pos) || board->at(pos)->getColor() == this->getColor())
                    pos.setValid(false);
                trajectory.push_back(pos);
            }


            // TODO
            // Add en-passent
            // en-passent will have to be thought about

        }
        bool Pawn::move(const Position& moveTo)
        {
            bool moved = Piece::move(moveTo);
            if (moved) firstMove = false;
            return moved;
        }
    }
}
