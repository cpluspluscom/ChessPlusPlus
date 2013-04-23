#include "Position.hpp"

namespace chesspp
{
    namespace board
    {
        Position::Position(void)
            :x(-1), y(-1), valid(true)
        {

        }
        Position::Position(const Position& other)
            :x(other.x), y(other.y), valid(other.valid)
        {

        }
        Position::Position(int x, int y)
            :x(x), y(y), valid(true)
        {

        }

        bool Position::inBounds(void) const
        {
            return x >= 0 && x < WIDTH && y >= 0 && y < WIDTH;
        }
        bool Position::isValid(void) const
        {
            return valid;
        }
        int Position::getX(void) const
        {
            return x;
        }
        int Position::getY(void) const
        {
            return y;
        }

        void Position::move(int x, int y)
        {
            this->x += x;
            this->y += y;
        }
        void Position::move(Direction d)
        {
            switch(d)
            {
            case NORTH:              y -= 1; break;
            case NORTH_EAST: x += 1; y -= 1; break;
            case EAST:       x += 1;         break;
            case SOUTH_EAST: x += 1; y += 1; break;
            case SOUTH:              y += 1; break;
            case SOUTH_WEST: x -= 1; y += 1; break;
            case WEST:       x -= 1;         break;
            case NORTH_WEST: x -= 1; y -= 1; break;
            }
        }
        void Position::set(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        void Position::setValid(bool v)
        {
            valid = v;
        }

        bool Position::operator==(const Position& other) const
        {
            return this->x == other.x && this->y == other.y;

        }
        bool Position::operator!=(const Position& other) const
        {
            // return !operator==(other); // ?
            return this->x != other.x || this->y != other.y;
        }

        std::ostream& operator<<(std::ostream& out, const Position& pos)
        {
            return out << "( " << pos.getX() << ", " << pos.getY() << ", " << ( pos.isValid()? 'V' : 'x' ) << ")";
        }
    }
}
