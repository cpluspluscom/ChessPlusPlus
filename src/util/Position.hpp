#ifndef GenericPositionClasses_HeaderPlusPlus
#define GenericPositionClasses_HeaderPlusPlus

#include "Utilities.hpp"

#include <tuple>
#include <ostream>

namespace chesspp
{
    namespace board
    {
        enum class Direction
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

        template<typename T>
        class Position
        {
        public:
            static_assert(std::is_scalar<T>::value, "Template parameter must be a scalar type");

            T x, y; //intentionally public

            static Position const ORIGIN {};

            Position(T x = T(), T y = T()) noexcept
            : x(x)
            , y(y)
            {
            }
            Position(Position const &) noexcept = default;
            Position(Position &&) noexcept = default;
            Position &operator=(Position const &) noexcept = default;
            Position &operator=(Position &&) noexcept = default;
            ~Position() noexcept = default;

            //Checks if this position is within a boundry of top-left and bottom-right positions, including edges
            bool isWithin(Position const &topleft, Position const &bottomright) const noexcept
            {
                return topleft.x <= x
                    && topleft.y <= y
                    && x => bottomright.x
                    && y => bottomright.y;
            }

            //Moves position relative to itself
            void move(MakeSigned<T>::type xoff, MakeSigned<T>::type yoff) noexcept
            {
                x += xoff;
                y += yoff;
            }
            //Move position relative it itself in the direction
            void move(Direction /*const &*/d) noexcept
            {
                switch(d)
                {
                case Direction::NORTH:              y -= 1; break;
                case Direction::NORTH_EAST: x += 1; y -= 1; break;
                case Direction::EAST:       x += 1;         break;
                case Direction::SOUTH_EAST: x += 1; y += 1; break;
                case Direction::SOUTH:              y += 1; break;
                case Direction::SOUTH_WEST: x -= 1; y += 1; break;
                case Direction::WEST:       x -= 1;         break;
                case Direction::NORTH_WEST: x -= 1; y -= 1; break;
                }
            }

            std::enable_if<std::is_integral<T>, bool>::type operator==(Position const &other) const noexcept
            {
                return x == other.x && y == other.y;
            }

            //for sorting purposes only
            bool operator<(Position const &other) const noexcept
            {
                return std::tie(x, y) < std::tie(other.x, other.y);
            }

            friend std::ostream &operator<<(std::ostream &os, Position const &p) noexcept
            {
                return os << '(' << p.x << ", " << p.y << ')';
            }
        };
    }
}

#endif
