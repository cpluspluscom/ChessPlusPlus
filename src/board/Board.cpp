#include "Board.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Board::Board(void)
            :pieces(WIDTH *WIDTH),  // WIDTH comes from Position.h
             currentPiece(NULL),
             selectedPiece(NULL)
        {
            // I think the initiator did this anyway
            for (PieceList::iterator iter = pieces.begin(); iter!=pieces.end(); iter++)
                *iter = NULL;
        }

        Board::~Board(void)
        {
            resetBoard();  // This deletes the pointers
        }

        void Board::resetBoard(void)
        {
            for (PieceList::iterator iter = pieces.begin(); iter!=pieces.end(); iter++)
            {
                delete *iter;
                *iter = NULL;
            }
        }

        bool Board::newGame(const std::string&fileName)
        {
            std::ifstream in(fileName);
            if (!in)
            {
                std::clog << "Could not open: " + fileName << std::endl;
                return false;
            }
            std::clog << fileName + " opened" << std::endl;

            // The board needs to be cleared
            // I guess this should happen after the file is opened
            this->resetBoard();

            char ch;                                     // To read from the file
            PieceList::iterator iter = pieces.begin();   // To iterate :)
            int pos = 0;                                 // To hopefully count 64 chars

            while (in >> ch)
            {
                if (iter == pieces.end())
                {
                    std::clog << "End of PieceList found before end of file" << std::endl;
                    return false;
                }

                switch(ch)
                {
                case'P':*iter=new Pawn(  Position( pos%WIDTH, pos/WIDTH), WHITE);break;
                case'R':*iter=new Rook(  Position( pos%WIDTH, pos/WIDTH), WHITE);break;
                case'N':*iter=new Knight(Position( pos%WIDTH, pos/WIDTH), WHITE);break;
                case'B':*iter=new Bishop(Position( pos%WIDTH, pos/WIDTH), WHITE);break;
                case'Q':*iter=new Queen( Position( pos%WIDTH, pos/WIDTH), WHITE);break;
                case'K':*iter=new King(  Position( pos%WIDTH, pos/WIDTH), WHITE);break;

                case'p':*iter=new Pawn(  Position( pos%WIDTH, pos/WIDTH), BLACK);break;
                case'r':*iter=new Rook(  Position( pos%WIDTH, pos/WIDTH), BLACK);break;
                case'n':*iter=new Knight(Position( pos%WIDTH, pos/WIDTH), BLACK);break;
                case'b':*iter=new Bishop(Position( pos%WIDTH, pos/WIDTH), BLACK);break;
                case'q':*iter=new Queen( Position( pos%WIDTH, pos/WIDTH), BLACK);break;
                case'k':*iter=new King(  Position( pos%WIDTH, pos/WIDTH), BLACK);break;

                case '*': /*No Piece Character */ break;

                default:
                    std::clog << "Invalid character found in new_game.txt" << std::endl;
                    return false;
                }
                ++iter;
                ++pos;
            }

            if (pos == 64) std::clog << "File size matched pieces size" << std::endl;
            else           std::clog << "File size did not match pieces size" << std::endl;


            in.close();

            // This can only be done when all of the pieces are on the board
            // In a real game, it should be for the color that has just moved first
            // So the other color can respond to things that may have cuased check
            // It should be its own function, as it is needed in move() also.

            for (PieceList::iterator iter = pieces.begin(); iter!=pieces.end(); iter++)
            {
                if (!*iter) continue;
                (*iter)->makeTrajectory(this);
            }
            return true;
        }

        int Board::posToInt(const Position&pos) const
        {
            // WIDTH defined in Position.h as 8
            return pos.getY() *WIDTH + pos.getX();
        }

        bool Board::hasPosition(const Position&pos) const
        {
            return pos.inBounds() &&pieces.at(posToInt(pos)) != NULL;
        }
        Piece*Board::at(const Position&pos) const
        {
            if (!pos.inBounds())
                return NULL;
            return pieces.at(posToInt(pos));
        }

        void Board::setCurrent(int screenX, int screenY)
        {
            static const int SIZE = 80;  // The pixel count of a square
            unsigned int idx = (screenY / SIZE) *WIDTH + (screenX / SIZE);
            if (idx >= pieces.size())
                currentPiece = NULL;
            else
                currentPiece = pieces.at(idx);
        }
        Piece*Board::getCurrent(void) const
        {
            return currentPiece;
        }
        void Board::setSelected(Piece*toSelect)
        {
            selectedPiece = toSelect;
        }
        Piece*Board::getSelected(void) const
        {
            return selectedPiece;
        }

        bool Board::move(Piece*toMove, int screenX, int screenY)
        {
            // Is the piece NULL
            if (!toMove)
            {
                std::cout << "BM: called With Null" << std::endl;
                return false;
            }

            // Is the piece in my list
            bool inList = false;
            for (PieceList::iterator iter = pieces.begin(); iter != pieces.end(); iter++)
                if (*iter == toMove) // Memory addresses
                    inList = true;
            if (!inList)
            {
                std::clog << "BM: Piece not Found" << std::endl;
                return false;
            }

            // Is the new position on the board?
            static const int SIZE = 80;  // Really need to define 80 somewhere
            int xPos = screenX / SIZE;
            int yPos = screenY / SIZE;
            Position moveTo(xPos, yPos);
            if (!moveTo.inBounds())
            {
                std::clog << "BM: Position out of bounds" << std::endl;
                return false;
            }

            // Remember the piece' idx and position
            int idxFrom = posToInt(toMove->getBoardPos());
            Position moveFrom(pieces.at(idxFrom)->getBoardPos());

            // Try to move the piece
            // This will return false if moveTo isn't in the piece's trajectory
            // (moveTo would also have to be valid in the trajectory, OnValidity.txt
            if (!toMove->move(moveTo))
            {
                std::clog << "BM: Couldn't move piece" << std::endl;
                return false;
            }

            // Is something very wrong? did Piece::move() actually fail?
            if (toMove->getBoardPos() != moveTo)
            {
                std::clog << "BM: Move didn't really work" << std::endl;
                return false;
            }


            // If this is a capture
            int idxTo = posToInt(moveTo);
            if (pieces.at(idxTo))
            {
                std::clog << "BM: Capturing piece: " << *pieces.at(idxTo) << std::endl;

                // At some point, we may want a capture list
                // This would be the time to do it
                // For now,
                delete pieces.at(idxTo);
            }

            // Move the piece on the board
            pieces.at(idxTo) = pieces.at(idxFrom);
            pieces.at(idxFrom) = NULL;

            // Recalcaulte trajectories
            // The piece that just moved certainly needs this
            pieces.at(idxTo)->makeTrajectory(this);

            for (PieceList::iterator iter = pieces.begin(); iter != pieces.end(); iter++)
            {

                if (!*iter || *iter == pieces.at(idxTo)) continue;

                // updateTrajectory checks if moveFrom or moveTo
                // are in the piece's trajectory
                // If either one is, the piece calls makeTrajectory()
                (*iter)->updateTrajectory(this, moveFrom, moveTo);
            }

            this->currentPiece = NULL; //reset currentPiece to avoid segfault.
            return true;
        }
    }
}
