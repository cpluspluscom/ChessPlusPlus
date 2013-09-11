#ifndef BishopChessPiece_HeaderPlusPlus
#define BishopChessPiece_HeaderPlusPlus

#include "Board.hpp"

namespace chesspp
{
    namespace board
    {
        class Bishop : public Piece
        {
        public:
            Bishop(Board &b, Position_t const &pos, Suit const &s);
            virtual ~Bishop() = default;

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
