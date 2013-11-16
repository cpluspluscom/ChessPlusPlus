#ifndef ArcherChessPiece_HeaderPlusPlus
#define ArcherChessPiece_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace piece
    {
        class Archer : public Piece
        {
        public:
            Archer(board::Board &b, Position_t const &pos, Suit const &s);
            virtual ~Archer() = default;

            virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const override;

        protected:
            virtual void calcTrajectory() override;

        private:
            virtual void moveUpdate(Position_t const &from, Position_t const &to) override;
        };
    }
}

#endif
