#include "Queen.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        Queen::Queen(board::Board &b, Position_t const &pos_, Suit const &s_)
        : Piece(b, pos_, s_)
        {
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Queen::texture() const
        {
            return board.config.texturePaths().at(suit).at("Queen");
        }

        void Queen::calcTrajectory()
        {
            //Queens can move infinitely in all eight directions
            using Dir = util::Direction;
            for(Dir d : {Dir::North
                        ,Dir::NorthEast
                        ,Dir::East
                        ,Dir::SouthEast
                        ,Dir::South
                        ,Dir::SouthWest
                        ,Dir::West
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
