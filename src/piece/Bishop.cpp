#include "Bishop.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        Bishop::Bishop(board::Board &b, Position_t const &pos_, Suit const &s_)
        : Piece(b, pos_, s_)
        {
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Bishop::texture() const
        {
            return board.config.texturePaths().at(suit).at("Bishop");
        }

        void Bishop::calcTrajectory()
        {
            //Bishops can move infinitely in the four diagonal directions
            using Dir = util::Direction;
            for(Dir d : {Dir::NorthEast
                        ,Dir::SouthEast
                        ,Dir::SouthWest
                        ,Dir::NorthWest})
            {
                Position_t t;
                for(signed i = 1; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addCapturing(t);
                    if(!board.occupied(t))
                    {
                        addTrajectory(t);
                    }
                    else break; //can't jump over pieces
                }
            }
        }
    }
}
