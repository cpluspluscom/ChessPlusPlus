#ifndef chesspp_piece_Archer_HeaderPlusPlus
#define chesspp_piece_Archer_HeaderPlusPlus

#include "board/Board.hpp"
#include "piece/Piece.hpp"

namespace chesspp
{
    namespace piece
    {
        class Archer
        : public virtual Piece
        {
        public:
            Archer(board::Board &b, Position_t const &pos, Suit_t const &s, Class_t const &pc);

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
