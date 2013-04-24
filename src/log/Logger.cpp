#include "Logger.hpp"

namespace chesspp
{
    namespace Log
    {
        std::ofstream Debug::out("debug.txt");
        int Debug::debugLevel = 0;
    }
}
