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
            Position(int x = -1, int y = -1);
            Position(Position const &other) = default;

            // Standard accessors
            bool inBounds() const;
            bool isValid() const;
            int getX() const;
            int getY() const;

            // Moves position relative to itself
            void move(int x, int y);
            // Move position relative it itself in the direction
            void move(Direction d);
            // Forces location of position
            void set(int x, int y);
            // Changes the validity
            void setValid(bool v);

            bool operator==(Position const &other) const;

            friend std::ostream&operator<<(std::ostream &out, Position const &pos);
        };
    }
}
#endif
