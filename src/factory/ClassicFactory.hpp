#ifndef ClassicChessGameFactoryClass_HeaderPlusPlus
#define ClassicChessGameFactoryClass_HeaderPlusPlus

#include "Factory.hpp"

#include "board/Board.hpp"

namespace chesspp
{
    namespace factory
    {
        class ClassicFactory : Factory
        {
            config::BoardConfig const &board_config;
            Factory_t cf;

        public:
            ClassicFactory(config::BoardConfig const &bc);

            virtual Factory_t const &factory() const override;
        };
    }
}

#endif
