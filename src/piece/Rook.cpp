#include "Rook.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        Rook::Rook(board::Board &b, Position_t const &pos_, Suit const &s_)
        : Piece(b, pos_, s_)
        , castling(b.getInteraction<board::Castling>())
        {
            //not yet moved, can castle
            castling.addFast(this);
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Rook::texture() const
        {
            return board.config.texturePaths().at(suit).at("Rook");
        }

        void Rook::calcTrajectory()
        {
            //Rooks can move infinitely in the four straight directions
            using Dir = util::Direction;
            for(Dir d : {Dir::North
                        ,Dir::East
                        ,Dir::South
                        ,Dir::West})
            {
                Position_t t;
                for(signed i = 1; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addCapturing(t);
                    if(board.occupied(t))
                    {
                        addTrajectory(t);
                    }
                    else break; //can't jump over pieces
                }
            }
        }

        void Rook::moveUpdate(Position_t const &from, Position_t const &to)
        {
            //moved, can no longer castle
            castling.removeFast(this);
        }
    }
}
