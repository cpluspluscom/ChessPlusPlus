#ifndef LOWKNIGHT_H
#define LOWKNIGHT_H

// Warning:
//    Texture positions are hard coded into constructor
//    I think they should at least be brought to the Board
//    So they can be changed at once

#include "Piece.hpp"

namespace chesspp
{
    namespace board
    {
        class Knight : public Piece
        {
        private:
            // The King also has this function.  I didn't add it to Piece
            // Because other pieces should use other methods
            // Maybe named a little poorly
            // x and y are offsets from the piece
            // if this position is ou-of-bounds, then nothing is added
            void addPosition(const Board* board, int x, int y);

        public:
            Knight(const Position& bPos, Color c);

            // Make the trajectory, see OnValidity.txt for a some info
            virtual void makeTrajectory(const Board* board);
        };
    }
}

#endif
