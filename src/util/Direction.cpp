#include "Direction.hpp"

#include <iostream>

namespace chesspp
{
    namespace util
    {
        Direction Rotate(Direction d, signed r) noexcept
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
                default:                             break;
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
                default:                             break;
                }
            }
            return d;
        }
        std::ostream &operator<<(std::ostream &os, Direction const &d) noexcept
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
            case D::None:      return os << "None";
            }
        }
        std::istream &operator>>(std::istream &is, Direction &d)
        {
            using D = Direction;
            std::string ds;
            is >> ds;
            if     (ds == "North"    ) return (d = D::North    ), is;
            else if(ds == "NorthEast") return (d = D::NorthEast), is;
            else if(ds == "East"     ) return (d = D::East     ), is;
            else if(ds == "SouthEast") return (d = D::SouthEast), is;
            else if(ds == "South"    ) return (d = D::South    ), is;
            else if(ds == "SouthWest") return (d = D::SouthWest), is;
            else if(ds == "West"     ) return (d = D::West     ), is;
            else if(ds == "NorthWest") return (d = D::NorthWest), is;
            else                       return (d = D::None     ), is;
        }
    }
}
