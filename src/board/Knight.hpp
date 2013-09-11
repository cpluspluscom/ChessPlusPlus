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

		private:
			virtual void moveUpdate(Position_t const &from, Position_t const &to);
        };
    }
}

#endif
