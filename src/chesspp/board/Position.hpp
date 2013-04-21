#ifndef LOWPOSITION_H
#define LOWPOSITION_H

// Notes:
//  Positions have a boolean "valid" member.  This is not to be confused
//  with an out-of-bounds Position.  Please see "OnValidity.txt" for more

#include <ostream>

namespace chesspp
{
    namespace board
    {
        // WIDTH is used throughout the game logic
        static std::size_t const WIDTH {8};

        enum Direction
        {
            NORTH,
            NORTH_EAST,
            EAST,
            SOUTH_EAST,
            SOUTH,
            SOUTH_WEST,
            WEST,
            NORTH_WEST
        };

        class Position
        {
        private:

            // The location of the piece
            int x;
            int y;

            // A valid position is one that the Piece can move to
            bool valid;

        public:
            Position(void);
            Position(const Position& other);
            Position(int x, int y);

            // Standard accessors
            bool inBounds(void) const;
            bool isValid(void) const;
            int getX(void) const;
            int getY(void) const;

            // Moves position relative to itself
            void move(int x, int y);
            // Move position relative it itself in the direction
            void move(Direction d);
            // Forces location of position
            void set(int x, int y);
            // Changes the validity
            void setValid(bool v);

            bool operator==(const Position& other) const;
            bool operator!=(const Position& other) const;  // Not Used

            friend std::ostream& operator<<(std::ostream& out, const Position& pos);

        };
    }
}
#endif
