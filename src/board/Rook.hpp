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

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveUpdate(Position_t const &from, Position_t const &to);
        };
    }
}

#endif
