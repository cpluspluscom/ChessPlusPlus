#ifndef ChessPlusPlus_Piece_PawnChessPiece_HeaderPlusPlus
#define ChessPlusPlus_Piece_PawnChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Pawn : public virtual Piece
        {
            bool en_passant = true;
            util::Direction facing;

        public:
            Pawn(board::Board &b, Position_t const &pos, Suit const &s, util::Direction const &face);

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

            virtual void tick(Position_t const &p) override;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
