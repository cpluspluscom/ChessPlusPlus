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
        inline Direction Rotate(Direction d, signed r) noexcept
        {
            using D = Direction;
            for(signed i = 0; i < r; ++i) //rotate positively
            {
                switch(d)
                {
                case D::North:     d = D::NorthEast; break;
                case D::NorthEast: d = D::East;      break;
                case D::East:      d = D::SouthEast; break;
                case D::SouthEast: d = D::South;     break;
                case D::South:     d = D::SouthWest; break;
                case D::SouthWest: d = D::West;      break;
                case D::West:      d = D::NorthWest; break;
                case D::NorthWest: d = D::North;     break;
                }
            }
            for(signed i = 0; i > r; --i) //rotate negatively
            {
                switch(d)
                {
                case D::North:     d = D::NorthWest; break;
                case D::NorthEast: d = D::North;     break;
                case D::East:      d = D::NorthEast; break;
                case D::SouthEast: d = D::East;      break;
                case D::South:     d = D::SouthEast; break;
                case D::SouthWest: d = D::South;     break;
                case D::West:      d = D::SouthWest; break;
                case D::NorthWest: d = D::West;      break;
                }
            }
            return d;
        }
        /**
         * Serializes a direction to a stream in string format.
         * \param os The stream to serialize to.
         * \param d the Direction to serialize.
         * \return os
         */
        inline std::ostream &operator<<(std::ostream &os, Direction const &d) noexcept
        {
            using D = Direction;
            switch(d)
            {
            case D::North:     return os << "North";
            case D::NorthEast: return os << "NorthEast";
            case D::East:      return os << "East";
            case D::SouthEast: return os << "SouthEast";
            case D::South:     return os << "South";
            case D::SouthWest: return os << "SouthWest";
            case D::West:      return os << "West";
            case D::NorthWest: return os << "NorthWest";
            }
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
             * \param x_ the x coordinate of this position, or T()
             * \param y_ the y coordinate of this position, or T()
             */
            Position(T x_ = T(), T y_ = T()) noexcept
            : x(x_)
            , y(y_)
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
                using D = Direction;
                for(signed i = 0; i < times; ++i)
                {
                    //move forward
                    switch(d)
                    {
                    case D::North:          --y; break;
                    case D::NorthEast: ++x; --y; break;
                    case D::East:      ++x;      break;
                    case D::SouthEast: ++x; ++y; break;
                    case D::South:          ++y; break;
                    case D::SouthWest: --x; ++y; break;
                    case D::West:      --x;      break;
                    case D::NorthWest: --x; --y; break;
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
             * \param a the left-hand position.
             * \param b the right-hand position
             * \return whether a equals b.
             */
            friend auto operator==(Position const &a, Position const &b) noexcept -> typename std::enable_if<std::is_integral<T>::value, bool>::type
            {
                return std::tie(a.x, a.y) == std::tie(b.x, b.y);
            }

            /**
             * Less-than comparison operator, to be used for
             * sorting purposes only.
             * \param a the left-hand position.
             * \param b the right-hand position.
             * \return true if a comes before b.
             */
            friend bool operator<(Position const &a, Position const &b) noexcept
            {
                return std::tie(a.x, a.y) < std::tie(b.x, b.y);
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
