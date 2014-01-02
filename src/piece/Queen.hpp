#ifndef ChessPlusPlus_Piece_QueenChessPiece_HeaderPlusPlus
#define ChessPlusPlus_Piece_QueenChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Queen : public virtual Piece
        {
        public:
            Queen(board::Board &b, Position_t const &pos, Suit const &s);

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
