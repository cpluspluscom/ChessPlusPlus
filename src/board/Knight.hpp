#ifndef KnightChessPiece_HeaderPlusPlus
#define KnightChessPiece_HeaderPlusPlus

#include "Board.hpp"

namespace chesspp
{
    namespace board
    {
        class Knight : public Piece
        {
        public:
            Knight(Board &b, Position_t const &pos, Suit const &s);
            virtual ~Knight() = default;

        protected:
            virtual void calcTrajectory() override;
    }
}

#endif
