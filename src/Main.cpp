#include <iostream>
#include <fstream>
#include <streambuf>

#include "Application.hpp"
#include "Debug.hpp"

int main()
{
    LogUtil lu; //replaces std::clog, std::cerr, std::cout with file streams

    try
    {
        return chesspp::Application().Exec();
    }
    catch(chesspp::Exception &e)
    {
        std::clog << "Caught in main: " << e.fullMessage() << std::endl;
        return -1;
    }
}
