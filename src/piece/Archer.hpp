#ifndef ChessPlusPlus_Piece_ArcherChessPiece_HeaderPlusPlus
#define ChessPlusPlus_Piece_ArcherChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Archer : public virtual Piece
        {
        public:
            Archer(board::Board &b, Position_t const &pos, Suit const &s);

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveUpdate(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
