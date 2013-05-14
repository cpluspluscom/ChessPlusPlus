#include "Board.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Board::Board(config::BoardConfig const &conf)
        : xsize(conf.getBoardWidth())
        , ysize(conf.getBoardHeight())
        {
            //This code needs to be abstracted so it is more modular

            pieces.clear();

            int pos = 0; //To hopefully count 64 chars

            for(char ch : conf.initialLayout())
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
                    std::clog << "Invalid character found in initial layout: '" << ch << "'" << std::endl;
                    return false;
                }
                if(np)
                {
                    pieces[p] = np;
                }
            }

            std::clog << "Layout size (" << pos << ") did ";
            if(pos != xsize*ysize)
            {
                std::clog << "not " << std::endl;
            }
            std::clog << "match expected size (" << xsize*ysize << ")" << std::endl;

            //This can only be done when all of the pieces are on the board
            //In a real game, it should be for the suit that has just moved first
            //So the other suit can respond to things that may have cuased check
            //It should be its own function, as it is needed in move() also.

            for(auto it = pieces.begin(); it != pieces.end(); ++it)
            {
                it->second->makeTrajectory();
            }
            return true;
        }

        bool Board::move(Position_t const &source, Position_t const &target)
        {
            if(pieces.find(source) == pieces.end())
            {
                std::cerr << "source position of piece to move does not contain a piece: " << source << std::endl;
                return false;
            }
            if(!valid(target))
            {
                std::cerr << "target position of piece to move is out of bounds: " << target << std::endl;
                return false;
            }

            Piece *tomove = pieces[source];
            pieces[target].swap(pieces[source]); //swap positions
            pieces.erase(source); //remove the one that used to be at target
            tomove.move(target);

            //Update the trajectories of pieces whose trajectories contain the the old oer new position
            for(auto it = pieces.begin(); it != pieces.end(); ++it)
            {
                Piece::PosList_t const &t = it->second->trajectory;
                if(t.find(source) != t.end() || t.find(target) != t.end()) //source or target found
                {
                    it->second->makeTrajectory(); //update
                }
            }

            return true;
        }
    }
}
