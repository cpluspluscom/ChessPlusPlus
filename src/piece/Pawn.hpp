#ifndef chesspp_piece_Pawn_HeaderPlusPlus
#define chesspp_piece_Pawn_HeaderPlusPlus

#include "board/Board.hpp"
#include "piece/Piece.hpp"

namespace chesspp
{
    namespace piece
    {
        class Pawn
        : public virtual Piece
        {
            bool en_passant = true;
            util::Direction facing;

        public:
            Pawn(board::Board &b, Position_t const &pos, Suit_t const &s, Class_t const &pc, util::Direction const &face);

            virtual void tick(Position_t const &p) override;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
