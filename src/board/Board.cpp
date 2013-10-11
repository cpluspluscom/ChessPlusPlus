#include "Board.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Board::Piece::Piece(Board &b, Position_t const &pos_, Suit const &s_)
        : board(b)
        , p(pos_)
        , s(s_)
        {
            std::clog << "Creation of " << *this << std::endl;
        }

        void Board::update(Position_t const &pos)
        {
            trajectories.clear();
            capturings.clear();
            capturables.clear();
            for(auto &p : pieces)
            {
                p->tick(pos);
                p->makeTrajectory();
            }
        }

        bool Board::capture(Pieces_t::iterator source, Movements_t::const_iterator target)
        {
            if(source == pieces.end())
            {
                std::cerr << "source iterator of piece to capture with is invalid" << std::endl;
                return false;
            }

            pieces.erase(target->first); //remove the target
            return move(source, target); //re-use existing code
        }
        bool Board::move(Pieces_t::iterator source, Movements_t::const_iterator target)
        {
            if(source == pieces.end())
            {
                std::cerr << "source iterator of piece to move is invalid" << std::endl;
                return false;
            }
            if(target == trajectories.end() && target == capturings.end())
            {
                std::cerr << "target iterator of position to move to is invalid" << std::endl;
                return false;
            }
            if(target->first != pieces.end())
            {
                std::cerr << "target iterator to move to contains a piece: " << target->second << " -> " << **(target->first) << std::endl;
                return false;
            }

            (*source)->move(target->second);
            update(target->second);
            std::clog << "Moved piece at " << (*source)->pos << " to " << target->second << std::endl;
            return true;
        }
    }
}
