#ifndef ChessPlusPlus_Piece_BishopChessPiece_HeaderPlusPlus
#define ChessPlusPlus_Piece_BishopChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Bishop : public virtual Piece
        {
        public:
            Bishop(board::Board &b, Position_t const &pos, Suit const &s);

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
