#include "Pawn.hpp"

#include <iostream>

namespace chesspp
{
    namespace piece
    {
        Pawn::Pawn(board::Board &b, Position_t const &pos_, Suit const &s_, util::Direction const &face)
        : Piece(b, pos_, s_)
        , facing(face)
        {
        }

        config::BoardConfig::Textures_t::mapped_type::mapped_type const &Pawn::texture() const
        {
            return board.config.texturePaths().at(suit).at("Pawn");
        }

        void Pawn::tick(Position_t const &m)
        {
            if(moves == 1 && m != pos)
            { //moved just happened, en passant no longer allowed
                en_passant = false;
            }
        }

        void Pawn::calcTrajectory()
        {
            //Pawns can move 1 or 2 spaces forward on their first turn,
            //or only 1 space forward on any other turn.
            //On any turn they can move diagonally forward to capture,
            //but may not capture when moving straight forward.
            //They may be captured via the space behind them
            //if they just moved forward two spaces (en passant).

            addTrajectory(Position_t(pos).move(facing));
            if(moves == 0) //first move
            {
                if(!board.occupied(Position_t(pos).move(facing))) //can't jump over pieces
                {
                    addTrajectory(Position_t(pos).move(facing, 2));
                }
            }
            else if(moves == 1 && en_passant) //just moved 2 spaces forward
            {
                addCapturable(Position_t(pos).move(facing, -1)); //enable en passant
            }

            Position_t diagr = Position_t(pos).move(Rotate(facing, +1));
            if(board.valid(diagr)) //can capture diagonally forward-right
            {
                addCapturing(diagr);
            }
            Position_t diagl = Position_t(pos).move(Rotate(facing, -1));
            if(board.valid(diagl)) //can capture diagonally forward-left
            {
                addCapturing(diagl);
            }
        }
    }
}
