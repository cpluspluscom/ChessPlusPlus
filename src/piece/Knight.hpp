#ifndef KnightChessPiece_HeaderPlusPlus
#define KnightChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Knight : public Piece
        {
        public:
            Knight(board::Board &b, Position_t const &pos, Suit const &s);
            virtual ~Knight() = default;

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveUpdate(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
