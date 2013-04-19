#ifndef LOGGER_H
#define LOGGER_H

// The logger is basically a static ofstream
// I wanted something other than the console to put
// real time data.  I don't think it worked, but it's okay

#include <fstream>
#include <string>

namespace chesspp
{
    namespace Log
    {
        class Debug
        {
        private:
            static std::ofstream out;
        public:

            // The debugLevel determins if there is output
            // the write() are passed their own level
            // if the debugLevel is less than the passed value
            // then data is written
            // Ideally the debugLevel would be set in a file
            // So that various levels of debugging can be done without a recompile
            static int debugLevel;

            template<typename T>
            static void write(T data, int level = 0)
            {
                out.open("debug.txt", std::ios::app);
                if (level > debugLevel) return;
                out << data;
                out.close();
            }
            template<typename T>
            static void writeln(T data, int level = 0)
            {
                out.open("debug.txt", std::ios::app);
                if (level > debugLevel) return;
                out << data << std::endl;
                out.close();
            }
        };
    }
}

#endif
