#include "Piece.hpp"

#include "board/Board.hpp"

#include <algorithm>

namespace chesspp
{
    namespace piece
    {
        Piece::Piece(board::Board &b, Position_t const &pos_, Suit_t const &s_, Class_t const &pc)
        : board(b) //can't use {}
        , p{pos_}
        , s{s_}
        , c{pc}
        {
            std::clog << "Creation of " << *this << std::endl;
        }

        void Piece::addTrajectory(Position_t const &tile)
        {
            if(board.valid(tile))
            {
                board.trajectories.insert(board::Board::Movements_t::value_type(board.find(this), tile));
            }
        }
        void Piece::removeTrajectory(Position_t const &tile)
        {
            auto range = board.trajectories.equal_range(board.find(this));
            for(auto it = range.first; it != range.second; )
            {
                if(it->second == tile)
                {
                    it = board.trajectories.erase(it);
                }
                else ++it;
            }
        }

        void Piece::addCapturing(Position_t const &tile)
        {
            if(board.valid(tile))
            {
                board.capturings.insert(board::Board::Movements_t::value_type(board.find(this), tile));
            }
        }
        void Piece::removeCapturing(Position_t const &tile)
        {
            auto range = board.capturings.equal_range(board.find(this));
            for(auto it = range.first; it != range.second; )
            {
                if(it->second == tile)
                {
                    it = board.capturings.erase(it);
                }
                else ++it;
            }
        }

        void Piece::addCapturable(Position_t const &tile)
        {
            if(board.valid(tile))
            {
                board.capturables.insert(board::Board::Movements_t::value_type(board.find(this), tile));
            }
        }
        void Piece::removeCapturable(Position_t const &tile)
        {
            auto range = board.capturables.equal_range(board.find(this));
            for(auto it = range.first; it != range.second; )
            {
                if(it->second == tile)
                {
                    it = board.capturables.erase(it);
                }
                else ++it;
            }
        }
    }
}
