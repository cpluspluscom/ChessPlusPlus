#ifndef ChessPlusPlus_Piece_QueenChessPiece_HeaderPlusPlus
#define ChessPlusPlus_Piece_QueenChessPiece_HeaderPlusPlus

#include "board/Board.hpp"
#include "piece/Piece.hpp"

namespace chesspp
{
    namespace piece
    {
        class Queen : public virtual Piece
        {
        public:
            Queen(board::Board &b, Position_t const &pos, Suit_t const &s, Class_t const &pc);

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
