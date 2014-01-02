#include "Archer.hpp"

#include <iostream>
#include <initializer_list>

namespace chesspp
{
    namespace piece
    {
        static auto ArcherRegistration = board::Board::registerPieceClass
        (
            "Archer",
            [](board::Board &b, board::Board::Position_t const &p, board::Board::Suit const &s)
            -> board::Board::Pieces_t::value_type
            {
                return board::Board::Pieces_t::value_type(new Archer(b, p, s));
            }
        );

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
            //Archers can be captured at four spots around them
            using Dir = util::Direction;
            for(Dir d : {Dir::North
                        ,Dir::East
                        ,Dir::South
                        ,Dir::West})
            {
                Position_t t = Position_t(pos).move(d);
                addCapturable(t);
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
