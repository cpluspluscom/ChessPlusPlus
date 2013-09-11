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
            North,
            NorthEast,
            East,
            SouthEast,
            South,
            SouthWest,
            West,
            NorthWest
        };
        inline Direction Rotate(Direction const &d, signed r)
        { //Hacky solution, should replace with better solution later
            Direction t {d};
            for(signed i = 0; i < r; ++i)
            {
                t = static_cast<Direction>((static_cast<int>(t)+1)%8);
            }
            for(signed i = 0; i > r; --i)
            {
                int n = static_cast<int>(t)-1;
                t = static_cast<Direction>(n < 0 ? n + 8 : n);
            }
			return t;
        }

        template<typename T>
        class Position
        {
        public:
            static_assert(std::is_scalar<T>::value, "Template parameter must be a scalar type");

			using value_type = T;

            T x, y; //intentionally public

			static Position const &Origin() noexcept
			{
				static Position origin;
				return origin;
			}

            Position(T x = T(), T y = T()) noexcept
            : x(x)
            , y(y)
            {
            }
            Position(Position const &) noexcept = default;
            Position(Position &&) noexcept = default;
            Position &operator=(Position const &) noexcept = default;
            Position &operator=(Position &&) noexcept = default;
            ~Position() = default;

            //Checks if this position is within a boundry of top-left and bottom-right positions, including edges
            bool isWithin(Position const &topleft, Position const &bottomright) const noexcept
            {
                return topleft.x <= x
                    && topleft.y <= y
                    && x >= bottomright.x
                    && y >= bottomright.y;
            }

            //Moves position relative to itself
            Position move(typename MakeSigned<T>::type xoff, typename MakeSigned<T>::type yoff) noexcept
            {
                x += xoff;
                y += yoff;
				return *this;
            }
            //Move position relative to itself in the direction the given number of times
            Position &move(Direction const &d, signed times = 1) noexcept
            {
                for(signed i = 0; i < times; ++i)
                {
                    //move forward
                    switch(d)
                    {
                    case Direction::North:          --y; break;
                    case Direction::NorthEast: ++x; --y; break;
                    case Direction::East:      ++x;      break;
                    case Direction::SouthEast: ++x; --y; break;
                    case Direction::South:          ++y; break;
                    case Direction::SouthWest: --x; ++y; break;
                    case Direction::West:      --x;      break;
                    case Direction::NorthWest: --x; --y; break;
                    }
                }
                if(times < 0)
                {
                    //move backward
                    Position t = Position(0, 0).move(d, -times);
                    move(-t.x, -t.y);
                }
                return *this;
            }

            typename std::enable_if<std::is_integral<T>::value, bool>::type operator==(Position const &other) const noexcept
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
