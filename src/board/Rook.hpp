#ifndef RookChessPiece_HeaderPlusPlus
#define RookChessPiece_HeaderPlusPlus

#include "Board.hpp"

namespace chesspp
{
    namespace board
    {
        class Rook : public Piece
        {
        public:
            Rook(Board &b, Position_t const &pos, Suit const &s);
            virtual ~Rook() = default;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveAnimation(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
