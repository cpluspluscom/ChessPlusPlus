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
            board.pieceTrajectories().add(*this, tile);
        }
        void Piece::removeTrajectory(Position_t const &tile)
        {
            board.pieceTrajectories().remove(*this, tile);
        }

        void Piece::addCapturing(Position_t const &tile)
        {
            board.pieceCapturings().add(*this, tile);
        }
        void Piece::removeCapturing(Position_t const &tile)
        {
            board.pieceCapturings().remove(*this, tile);
        }

        void Piece::addCapturable(Position_t const &tile)
        {
            board.pieceCapturables().add(*this, tile);
        }
        void Piece::removeCapturable(Position_t const &tile)
        {
            board.pieceCapturables().remove(*this, tile);
        }
    }
}
