#ifndef KingChessPiece_HeaderPlusPlus
#define KingChessPiece_HeaderPlusPlus

#include "board/Board.hpp"
#include "board/Castling.hpp"

namespace chesspp
{
    namespace piece
    {
        class King : public Piece
        {
            Castling &castling;

        public:
            King(Board &b, Position_t const &pos, Suit const &s);
            virtual ~King() = default;

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveUpdate(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
