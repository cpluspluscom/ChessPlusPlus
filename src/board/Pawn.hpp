#ifndef PawnChessPiece_HeaderPlusPlus
#define PawnChessPiece_HeaderPlusPlus

#include "Board.hpp"

namespace chesspp
{
    namespace board
    {
        class Pawn : public Piece
        {
            bool en_passant = false;
            Direction facing;

        public:
            Pawn(Board &b, Position_t const &pos, Suit const &s, Direction const &face);
            virtual ~Pawn() = default;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveAnimation(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
