#include "Archer.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        Archer::Archer(board::Board &b, Position_t const &pos_, Suit const &s_)
        : Piece(b, pos_, s_)
        {
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Archer::texture() const
        {
            return board.config.texturePaths().at(suit).at("Archer");
        }

        void Archer::calcTrajectory()
        {
            //Archers can move one space in four directions
            using Dir = util::Direction;
            for(Dir d : {Dir::NorthEast
                        ,Dir::SouthEast
                        ,Dir::SouthWest
                        ,Dir::NorthWest})
            {
                Position_t t = Position_t(pos).move(d);
                addTrajectory(t);
            }
            //Archers can only capture at a circle around them
            for(Position_t m : {Position_t( 1, -2)
                               ,Position_t( 2, -1)
                               ,Position_t( 2,  1)
                               ,Position_t( 1,  2)
                               ,Position_t(-1,  2)
                               ,Position_t(-2,  1)
                               ,Position_t(-2, -1)
                               ,Position_t(-1, -2)
                               ,Position_t( 0,  2)
                               ,Position_t(-2,  0)
                               ,Position_t( 2,  0)
                               ,Position_t( 0, -2)})
            {
                Position_t t = Position_t(pos).move(m.x, m.y);
                addCapturing(t);
            }
        }

        void Archer::moveUpdate(Position_t const &from, Position_t const &to)
        {
        }
    }
}
