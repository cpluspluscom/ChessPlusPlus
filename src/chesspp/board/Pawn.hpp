#ifndef LOWPAWN_H
#define LOWPAWN_H

// Warning:
//    Texture positions are hard coded into constructor
//    I think they should at least be brought to the Board
//    So they can be changed at once

#include "Piece.hpp"

namespace chesspp
{
    namespace board
    {
        class Pawn : public Piece
        {
        private:
            bool firstMove;

        public:
            Pawn(const Position& bPos, Color c);

            // Make the trajectory, see "OnValidity.txt" for more
            virtual void makeTrajectory(const Board* board);

            // In addition to calling Piece::move(),
            // this function changes "firstMove" to false
            virtual bool move(const Position& moveTo);
        };
    }
}
#endif
