#include "Board.hpp"

#include <iostream>

namespace chesspp
{
    namespace board
    {
        Board::Board(config::BoardConfig const &conf, Factory_t const &fact)
        : config(conf)
        , factory(fact)
        {
            for(auto const &slot : conf.initialLayout())
            {
                pieces.emplace(factory.at(slot.second.first)(*this, slot.first, slot.second.second));
            }

            for(auto const &p : pieces)
            {
                p->makeTrajectory();
            }
        }
        bool Board::occupied(Position_t const &pos) const
        {
            for(auto const &p : *this)
            {
                if(p->pos == pos)
                {
                    return true;
                }
            }
            return false;
        }

        Board::Pieces_t::const_iterator Board::begin() const
        {
            return pieces.begin();
        }

        Board::Pieces_t::const_iterator Board::end() const
        {
            return pieces.end();
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
            auto t = target->second;
            (*source)->move(t);
            update(t);
            std::clog << " to " << t << std::endl;
            return true;
        }

        Board::Movements const &Board::pieceTrajectories() const
        {
            return trajs;
        }

        Board::Movements const &Board::pieceCapturings() const
        {
            return captings;
        }

        Board::Movements const &Board::pieceCapturables() const
        {
            return captables;
        }

        Board::MovementsRange Board::pieceTrajectory(Piece const &p)
        {
            return trajectories.equal_range(p.self());
        }

        Board::MovementsRange Board::pieceCapturing(Piece const &p)
        {
            return capturings.equal_range(p.self());
        }

        Board::MovementsRange Board::pieceCapturable(Piece const &p)
        {
            return capturables.equal_range(p.self());
        }

        bool Board::valid(Position_t const &pos) const noexcept
        {
            return pos.isWithin(Position_t::Origin(), {config.boardWidth(), config.boardHeight()});
        }

        Board::Piece::Piece(Board &b, Position_t const &pos_, Suit const &s_)
        : board(b)
        , p(pos_)
        , s(s_)
        {
            std::clog << "Creation of " << *this << std::endl;
        }

        void Board::Piece::makeTrajectory()
        {
            addCapturable(pos);
            calcTrajectory();
        }

        void Board::Piece::addTrajectory(Position_t const &tile)
        {
            if(board.valid(tile))
            {
                board.trajectories.insert(Board::Movements_t::value_type(self(), tile));
            }
        }

        void Board::Piece::removeTrajectory(Position_t const &tile)
        {
            auto range = board.trajectories.equal_range(self());
            for(auto it = range.first; it != range.second; )
            {
                if(it->second == tile)
                {
                    it = board.trajectories.erase(it);
                }
                else ++it;
            }
        }

        void Board::Piece::addCapturing(Position_t const &tile)
        {
            if(board.valid(tile))
            {
                board.capturings.insert(Board::Movements_t::value_type(self(), tile));
            }
        }

        void Board::Piece::removeCapturing(Position_t const &tile)
        {
            auto range = board.capturings.equal_range(self());
            for(auto it = range.first; it != range.second; )
            {
                if(it->second == tile)
                {
                    it = board.capturings.erase(it);
                }
                else ++it;
            }
        }

        void Board::Piece::addCapturable(Position_t const &tile)
        {
            if(board.valid(tile))
            {
                board.capturables.insert(Board::Movements_t::value_type(self(), tile));
            }
        }

        void Board::Piece::removeCapturable(Position_t const &tile)
        {
            auto range = board.capturables.equal_range(self());
            for(auto it = range.first; it != range.second; )
            {
                if(it->second == tile)
                {
                    it = board.capturables.erase(it);
                }
                else ++it;
            }
        }

        void Board::Piece::tick(Position_t const &m)
        {
        }

        void Board::Piece::move(Position_t const &to)
        {
            Position_t from = pos;
            p = to;
            moveUpdate(from, to);
            ++movenum;
        }

        void Board::Piece::moveUpdate(Position_t const &from, Position_t const &to)
        {
        }

        bool Board::Pieces_t_iterator_compare::operator()(Board::Pieces_t::iterator const &a, Board::Pieces_t::iterator const &b) const
        {
            return *a < *b;
        }

        Board::Interaction::Interaction ( Board& b )
        : board(b)
        {
        }


        Board::Movements::Movements(Movements_t const &m_)
        : m(m_)
        {
        }

        Board::Movements_t::const_iterator Board::Movements::begin() const
        {
            return m.cbegin();
        }

        Board::Movements_t::const_iterator Board::Movements::end() const
        {
            return m.cend();
        }

        Board::MovementsRange::MovementsRange(std::pair<Movements_t::iterator, Movements_t::iterator> const &r_)
        : r(r_)
        {
        }

        Board::Movements_t::const_iterator Board::MovementsRange::begin() const
        {
            return r.first;
        }
        Board::Movements_t::const_iterator Board::MovementsRange::end() const
        {
            return r.second;
        }
    }
}
