#ifndef ChessGameFactoryAbstractClass_HeaderPlusPlus
#define ChessGameFactoryAbstractClass_HeaderPlusPlus

#include "board/Board.hpp"

namespace chesspp
{
    namespace factory
    {
        class Factory
        {
        public:
            using Factory_t = board::Board::Factory_t;

            virtual Factory_t const &factory() const = 0;
        };
    }
}

#endif
