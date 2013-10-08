#include "Board.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Board::Piece::Piece(Board &b, Position_t const &pos, Suit const &s)
        : board(b)
        , p(pos)
        , s(s)
        {
            std::clog << "Creation of " << *this << std::endl;
        }

        void Board::update(Position_t const &pos)
        {
            captures.clear();
            for(auto &p : pieces)
            {
                p.second->tick(pos);
                p.second->makeTrajectory();
            }
        }

        bool Board::capture(Position_t source, Captures_t::const_iterator target)
        {
            if(pieces.find(source) == pieces.end())
            {
                std::cerr << "source position of piece to move does not contain a piece: " << source << std::endl;
                return false;
            }

            pieces.erase(target->first); //remove the target
            return move(source, target->second); //re-use existing code
        }
        bool Board::move(Position_t source, Position_t target)
        {
            if(pieces.find(source) == pieces.end())
            {
                std::cerr << "source position of piece to move does not contain a piece: " << source << std::endl;
                return false;
            }
            if(pieces.find(target) != pieces.end())
            {
                std::cerr << "target position to move to contains a piece: " << target << " -> " << *pieces[target] << std::endl;
                return false;
            }

            auto &tomove = *pieces[source]; //grab pieces to be moved
            pieces[target].swap(pieces[source]); //swap unique_ptrs
            pieces.erase(source); //remove empty unique_ptr
            tomove.move(target); //update position

            update(tomove.pos);
        }
    }
}
