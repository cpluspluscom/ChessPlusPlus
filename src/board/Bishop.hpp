#ifndef LOWBISHOP_H
#define LOWBISHOP_H

// Warning:
//    Texture positions are hard coded into constructor
//    I think they should at least be brought to the Board
//    So they can be changed at once

#include "Piece.hpp"

namespace chesspp
{
    namespace board
    {
        class Bishop : public Piece
        {
        public:
            Bishop(Position const &bPos, Color c);

            virtual void makeTrajectory(Board const *board);
        };
    }
}

#endif
