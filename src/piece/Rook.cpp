#include "Rook.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        Rook::Rook(board::Board &b, Position_t const &pos, Suit const &s)
        : Piece(b, pos, s)
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
            std::clog << "Rook@" << pos << "->calcTrajectory()" << std::endl;

            //Rooks can move infinitely in the four straight directions
            using Dir = util::Direction;
            for(Dir d : {Dir::North
                        ,Dir::East
                        ,Dir::South
                        ,Dir::West})
            {
                Position_t t;
                for(signed i = 0; board.valid(t = Position_t(pos).move(d, i)); ++i)
                {
                    addTrajectory(t);
                    addCapturing(t);
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
