#ifndef RookChessPiece_HeaderPlusPlus
#define RookChessPiece_HeaderPlusPlus

#include "Board.hpp"
#include "Castling.hpp"

namespace chesspp
{
    namespace board
    {
        class Rook : public Piece
        {
            Castling &castling;

        public:
            Rook(Board &b, Position_t const &pos, Suit const &s);
            virtual ~Rook() = default;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveUpdate(Position_t const &from, Position_t const &to);
        };
    }
}

#endif
