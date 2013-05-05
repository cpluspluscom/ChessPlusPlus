#include "Board.hpp"

#include "Piece.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Board::Board(config::BoardConfig &conf)
        : xsize(conf.getBoardWidth())
        , ysize(conf.getBoardHeight())
        {
            //This code needs to be abstracted so it is more modular

            std::ifstream in(fileName);
            if(!in)
            {
                std::clog << "Could not open: " + fileName << std::endl;
                return false;
            }
            std::clog << fileName + " opened" << std::endl;

            pieces.clear();

            char ch;     // To read from the file
            int pos = 0; // To hopefully count 64 chars

            while(in >> ch)
            {
                Position_t p {pos%xsize, pos/xsize};
                ++pos;
                Piece *np = nullptr;
                switch(ch)
                {
                case 'P': np = new Pawn  (*this, p, WHITE); break;
                case 'R': np = new Rook  (*this, p, WHITE); break;
                case 'N': np = new Knight(*this, p, WHITE); break;
                case 'B': np = new Bishop(*this, p, WHITE); break;
                case 'Q': np = new Queen (*this, p, WHITE); break;
                case 'K': np = new King  (*this, p, WHITE); break;

                case 'p': np = new Pawn  (*this, p, BLACK); break;
                case 'r': np = new Rook  (*this, p, BLACK); break;
                case 'n': np = new Knight(*this, p, BLACK); break;
                case 'b': np = new Bishop(*this, p, BLACK); break;
                case 'q': np = new Queen (*this, p, BLACK); break;
                case 'k': np = new King  (*this, p, BLACK); break;

                case '*':                                   break;

                default:
                    std::clog << "Invalid character found in new_game.txt" << std::endl;
                    return false;
                }
                if(np)
                {
                    pieces[p] = np;
                }
            }

            if(pos == 64) std::clog << "File size matched pieces size" << std::endl;
            else          std::clog << "File size did not match pieces size" << std::endl;

            in.close();

            // This can only be done when all of the pieces are on the board
            // In a real game, it should be for the color that has just moved first
            // So the other color can respond to things that may have cuased check
            // It should be its own function, as it is needed in move() also.

            for(auto iter = pieces.begin(); iter != pieces.end(); ++iter)
            {
                (*iter)->makeTrajectory();
            }
            return true;
        }

        Piece *Board::at(Position const &pos) const
        {
            if(pieces.find(pos) == pieces.end())
            {
                return nullptr;
            }
            return pieces[pos];
        }

        bool Board::move(Piece *toMove, int screenX, int screenY)
        {
            // Is the piece nullptr
            if(!toMove)
            {
                std::cout << "BM: called With nullptr" << std::endl;
                return false;
            }

            // Is the piece in my list
            bool inList = false;
            for(auto iter = pieces.begin(); iter != pieces.end(); ++iter)
            {
                if(*iter == toMove) // Memory addresses
                {
                    inList = true;
                }
            }
            if(!inList)
            {
                std::clog << "BM: Piece not Found" << std::endl;
                return false;
            }

            // Is the new position on the board?
            static int const SIZE = 80;  // Really need to define 80 somewhere
            int xPos = screenX / SIZE;
            int yPos = screenY / SIZE;
            Position moveTo(xPos, yPos);
            if(!moveTo.inBounds())
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
            if(!toMove->move(moveTo))
            {
                std::clog << "BM: Couldn't move piece" << std::endl;
                return false;
            }

            // Is something very wrong? did Piece::move() actually fail?
            if(toMove->getBoardPos() != moveTo)
            {
                std::clog << "BM: Move didn't really work" << std::endl;
                return false;
            }


            // If this is a capture
            int idxTo = posToInt(moveTo);
            if(pieces.at(idxTo))
            {
                std::clog << "BM: Capturing piece: " << *pieces.at(idxTo) << std::endl;

                // At some point, we may want a capture list
                // This would be the time to do it
                // For now,
                delete pieces.at(idxTo);
            }

            // Move the piece on the board
            pieces.at(idxTo) = pieces.at(idxFrom);
            pieces.at(idxFrom) = nullptr;

            // Recalcaulte trajectories
            // The piece that just moved certainly needs this
            pieces.at(idxTo)->makeTrajectory(this);

            for(auto iter = pieces.begin(); iter != pieces.end(); ++iter)
            {

                if(!*iter || *iter == pieces.at(idxTo)) continue;

                // updateTrajectory checks if moveFrom or moveTo
                // are in the piece's trajectory
                // If either one is, the piece calls makeTrajectory()
                (*iter)->updateTrajectory(this, moveFrom, moveTo);
            }

            this->currentPiece = nullptr; //reset currentPiece to avoid segfault.
            return true;
        }
    }
}
