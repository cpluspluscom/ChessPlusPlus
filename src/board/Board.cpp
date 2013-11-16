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

        bool Board::capture(Pieces_t::iterator source, Movements_t::const_iterator target, Movements_t::const_iterator capturable)
        {
            if(source == pieces.end())
            {
                std::cerr << "source iterator of piece to capture with is invalid" << std::endl;
                return false;
            }
            if(source != target->first)
            {
                std::cerr << "target iterator does not match source iterator, source{" << **source << "}, target {" << **(target->first) << "}" << std::endl;
                return false;
            }
            if(capturable->second != target->second)
            {
                std::cerr << "capturable may not be captured at target" << std::endl;
            }

            pieces.erase(capturable->first);
            std::clog << "Capture: ";
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
                std::cerr << "target iterator of piece to move to is invalid" << std::endl;
                return false;
            }
            if(source != target->first)
            {
                std::cerr << "target iterator does not match source iterator, source{" << **source << "}, target {" << **(target->first) << "}" << std::endl;
                return false;
            }
            if(occupied(target->second))
            {
                std::cerr << "target iterator to move to is occupied:" << std::endl;
                for(auto &p : pieces)
                {
                    if(p->pos == target->second)
                    {
                        std::cerr << "\t" << *p << std::endl;
                    }
                }
                return false;
            }

            std::clog << "Moved piece at " << (*source)->pos << std::flush;
            (*source)->move(target->second);
            update(target->second);
            std::clog << " to " << target->second << std::endl;
            return true;
        }
    }
}
