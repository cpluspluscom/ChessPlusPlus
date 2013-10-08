#ifndef GenericPositionClasses_HeaderPlusPlus
#define GenericPositionClasses_HeaderPlusPlus

#include "Utilities.hpp"

#include <tuple>
#include <ostream>
#include <cstdint>

namespace chesspp
{
    namespace util
    {
        /**
         * Represents a direction.
         */
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
        /**
         * Returns a new direction which is a rotation of the
         * provided direction.
         * \param d the direction to rotate.
         * \param r the number of times to rotate, may be negative.
         * \return the rotated direction.
         */
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

        /**
         * Represents a two-dimensional point or position.
         * \tparam T coordinate type, must be a scalar type.
         */
        template<typename T>
        class Position
        {
        public:
            static_assert(std::is_scalar<T>::value, "Template parameter must be a scalar type");

            using value_type = T;

            T x, y; //intentionally public

            /**
             * Returns the position at the origin.
             * This position is the result of x and y
             * being initialized by T's default constructor.
             * \return the position at the origin.
             */
            static Position const &Origin() noexcept
            {
                static Position origin;
                return origin;
            }

            /**
             * Initializes x and y to the provided values,
             * or from T's default constructor otherwise.
             * \param x the x coordinate of this position, or T()
             * \param y the y coordinate of this position, or T()
             */
            Position(T x = T(), T y = T()) noexcept
            : x(x)
            , y(y)
            {
            }
            Position(Position const &) = default;
            Position(Position &&) = default;
            Position &operator=(Position const &) = default;
            Position &operator=(Position &&) = default;
            ~Position() = default;

            /**
             * Checks if this position is within a boundry of
             * top-left and bottom-right positions, including edges.
             * \param topleft the lowest coordinate corner
             * \param bottomright the highest coordinate corner
             * \return whether this position is inclusively within the given boundaries.
             */
            bool isWithin(Position const &topleft, Position const &bottomright) const noexcept
            {
                return topleft.x <= x
                    && topleft.y <= y
                    && x <= bottomright.x
                    && y <= bottomright.y;
            }

            /**
             * Moves this position relative to itself.
             * \param xoff the value to add to x, of type signed T
             * \param yoff the value to add to y, of type signed T
             * \return *this
             */
            Position &move(typename MakeSigned<T>::type xoff, typename MakeSigned<T>::type yoff) noexcept
            {
                x += xoff;
                y += yoff;
                return *this;
            }
            /**
             * Move position relative to itself in a direction
             * a given number of times.
             * \param d the dirction in which to move.
             * \param times the number of times to move in direction d.
             * \return *this
             */
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

            /**
             * Equality comparison operator.
             * \param other the position to compare to.
             * \return whether this position equals the other.
             */
            typename std::enable_if<std::is_integral<T>::value, bool>::type operator==(Position const &other) const noexcept
            {
                return x == other.x && y == other.y;
            }

            /**
             * Less-than comparison operator, to be used for
             * sorting purposes only.
             * \param other the position to compare to.
             * \return true if this position comes before the other.
             */
            bool operator<(Position const &other) const noexcept
            {
                return std::tie(x, y) < std::tie(other.x, other.y);
            }
        };

        /**
         * Serializes a position to a stream in the format "(x, y)".
         * This is the signed version.
         * \param os the stream to write to.
         * \param p the position to serialize into the stream.
         * \return os
         */
        template<typename T>
        typename std::enable_if<std::is_integral<T>::value && std::is_same<T, typename MakeSigned<T>::type>::value, std::ostream &>::type operator<<(std::ostream &os, Position<T> const &p) noexcept
        {
            //cast in case of char
            return os << '('  << static_cast<std::intmax_t>(p.x)
                      << ", " << static_cast<std::intmax_t>(p.y) << ')';
        }
        /**
         * Serializes a position to a stream in the format "(x, y)".
         * This is the unsigned version.
         * \param os the stream to write to.
         * \param p the position to serialize into the stream.
         * \return os
         */
        template<typename T>
        typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, typename MakeSigned<T>::type>::value, std::ostream &>::type operator<<(std::ostream &os, Position<T> const &p) noexcept
        {
            //cast in case of char
            return os << '('  << static_cast<std::uintmax_t>(p.x)
                      << ", " << static_cast<std::uintmax_t>(p.y) << ')';
        }
        /**
         * Serializes a position to a stream in the format "(x, y)".
         * This is the float version.
         * \param os the stream to write to.
         * \param p the position to serialize into the stream.
         * \return os
         */
        template<typename T>
        typename std::enable_if<!std::is_integral<T>::value, std::ostream &>::type operator<<(std::ostream &os, Position<T> const &p) noexcept
        {
            return os << '('  << p.x  << ", " << p.y << ')';
        }
    }
}

#endif
