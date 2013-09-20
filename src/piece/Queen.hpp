#ifndef QueenChessPiece_HeaderPlusPlus
#define QueenChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Queen : public Piece
        {
        public:
            Queen(Board &b, Position_t const &pos, Suit const &s);
            virtual ~Queen() = default;

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;
        };
    }
}

#endif
