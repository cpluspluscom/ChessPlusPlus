#include "King.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        static auto KingRegistration = board::Board::registerPieceClass
        (
            "King",
            [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s)
            -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new King(b, p, s));
            }
        );

        King::King(board::Board &b, Position_t const &pos_, Suit const &s_)
        : Piece{b, pos_, s_}
        , castling(b.getInteraction<board::Castling>()) //can't use {}
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
