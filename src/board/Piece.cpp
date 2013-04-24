#include "Piece.hpp"

namespace chesspp
{
    namespace board
    {
        Piece::Piece(const Position& bPos, const Position& tPos, Color c, Type t)
            : color(c), type(t), boardPos(bPos)
        {
            int tX = tPos.getX();
            int tY = tPos.getY() + ( c == WHITE ? 0 : 80 );
            texturePos.set(tX, tY);

            Log::Debug::writeln(*this);
        }


        const Position& Piece::getBoardPos(void) const
        {
            return boardPos;
        }
        const Position& Piece::getTexturePos(void) const
        {
            return texturePos;
        }
        Color Piece::getColor(void) const
        {
            return color;
        }

        const posList& Piece::getTrajectory(void) const
        {
            return trajectory;
        }
        void Piece::shootPath(const Board* board, const Direction d)
        {
            Position pos = this->boardPos;

            pos.move(d);

            // Validity only has to be changed to false
            // Please see "OnValidity.txt" for more info
            while (pos.inBounds())
            {
                if (board->hasPosition(pos))
                {
                    if (board->at(pos)->getColor() == this->color)
                    {
                        pos.setValid(false);
                        this->trajectory.push_back(pos);
                    }
                    else
                    {
                        this->trajectory.push_back(pos);
                        pos.setValid(false);
                    }
                }
                else
                {
                    this->trajectory.push_back(pos);
                }
                pos.move(d);
            }
        }
        void Piece::updateTrajectory(const Board* board, const Position& oldPos, const Position& newPos)
        {
            Log::Debug::writeln("Updating", 1);

            bool foundPos = false;
            for (posList::iterator iter = trajectory.begin(); iter != trajectory.end(); iter++)
            {
                if (*iter == oldPos || *iter == newPos)
                {
                    foundPos = true;
                    break;
                }
            }
            if (foundPos) makeTrajectory(board);
        }


        bool Piece::move(const Position& moveTo)
        {
            if (!moveTo.inBounds())
            {
                Log::Debug::write("PE: moveTo not in bounds: ");
                Log::Debug::writeln(moveTo);
                return false;
            }


            for (posList::iterator iter = trajectory.begin(); iter != trajectory.end(); iter++)
            {
                if (*iter == moveTo && iter->isValid())
                {
                    this->boardPos = moveTo;
                    Log::Debug::write("PE: moveTo success: ");
                    Log::Debug::write(moveTo);
                    Log::Debug::writeln(boardPos);
                    return true;
                }
            }
            Log::Debug::write("PE: moveTo fail: ");
            Log::Debug::write(moveTo);
            Log::Debug::writeln(boardPos);
            return false;
        }
        bool Piece::isPawn(void)
        {
            return false;
        }
        bool Piece::isKing(void)
        {
            return false;
        }

        Type Piece::getType( void ) const
        {
            return type;
        }




        std::ostream& operator<<(std::ostream& out, const Piece& p)
        {
            return out << "PIECE:  " << p.getBoardPos() << p.getTexturePos() << (p.getColor() == WHITE ? "WHITE" : "BLACK");
        }
    }
}
