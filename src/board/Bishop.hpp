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

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveAnimation(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
