#ifndef chesspp_piece_Knight_HeaderPlusPlus
#define chesspp_piece_Knight_HeaderPlusPlus

#include "board/Board.hpp"
#include "piece/Piece.hpp"

namespace chesspp
{
    namespace piece
    {
        class Knight
        : public virtual Piece
        {
        public:
            Knight(board::Board &b, Position_t const &pos, Suit_t const &s, Class_t const &pc);

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
