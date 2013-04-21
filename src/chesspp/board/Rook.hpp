#ifndef LOWROOK_H
#define LOWROOK_H

// Warning:
//    Texture positions are hard coded into constructor
//    I think they should at least be brought to the Board
//    So they can be changed at once

#include "Piece.hpp"

namespace chesspp
{
    namespace board
    {
        class Rook : public Piece
        {
        private:
        public:
            Rook(const Position& bPos, Color c);

            virtual void makeTrajectory(const Board* board);
        };
    }
}
#endif
