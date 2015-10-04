#include "Archer.hpp"

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
                return board::Board::Pieces_t::value_type(new Archer(b, p, s, "Archer"));
            }
        );

        Archer::Archer(board::Board &b, Position_t const &pos_, Suit_t const &s_, Class_t const &pc)
        : Piece{b, pos_, s_, pc}
        {
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
    }
}
