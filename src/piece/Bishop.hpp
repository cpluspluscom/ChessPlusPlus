#ifndef BishopChessPiece_HeaderPlusPlus
#define BishopChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Bishop : public Piece
        {
        public:
            Bishop(board::Board &b, Position_t const &pos, Suit const &s);
            virtual ~Bishop() = default;

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
