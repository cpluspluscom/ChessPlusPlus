#include "Bishop.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace board
    {
        Bishop::Bishop(Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
        {
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Bishop::texture() const
        {
            return board.config.texturePaths().at(suit).at("Bishop");
        }

        void Bishop::calcTrajectory()
        {
            std::clog << "Bishop@" << pos << "->calcTrajectory()" << std::endl;

            //Bishops can move infinitely in the four diagonal directions
            using Dir = util::Direction;
            for(Dir d : {Dir::NorthEast
                        ,Dir::SouthEast
                        ,Dir::SouthWest
                        ,Dir::NorthWest})
            {
                Position_t t;
                for(signed i = 0; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addTrajectory(t);
                    addCapturing(t);
                }
            }
        }
    }
}
