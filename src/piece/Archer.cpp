#include "Archer.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        Archer::Archer(board::Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
        {
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Archer::texture() const
        {
            return board.config.texturePaths().at(suit).at("Archer");
        }

        void Archer::calcTrajectory()
        {
            std::clog << "Archer@" << pos << "->calcTrajectory()" << std::endl;

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
			for(Position_t p : {Position_t( 1, -2)
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
                Position_t t = Position_t(pos).move(p.x, p.y);
                addCapturing(t);
            }
        }

        void Archer::moveUpdate(Position_t const &from, Position_t const &to)
        {
        }
    }
}
