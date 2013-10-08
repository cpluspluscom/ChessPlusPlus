#include "King.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        King::King(board::Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
        , castling(b.getInteraction<board::Castling>())
        {
            //not yet moved, can castle
            castling.addSlow(this);
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &King::texture() const
        {
            return board.config.texturePaths().at(suit).at("King");
        }

        void King::calcTrajectory()
        {
            //Kings can move one space in all eight directions
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
                Position_t t = Position_t(pos).move(d);
                addTrajectory(t);
                addCapturing(t);
            }
        }

        void King::moveUpdate(Position_t const &from, Position_t const &to)
        {
            //moved, can no longer castle
            castling.removeSlow(this);
        }
    }
}
