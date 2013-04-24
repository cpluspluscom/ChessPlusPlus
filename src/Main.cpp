#include <iostream>

#include "Application.hpp"

int main()
{
    try
    {
        return chesspp::Application().Exec();
    }
    catch (chesspp::Exception &e)
    {
        std::clog << "Caught in main: " << e.fullMessage() << std::endl;
        return -1;
    }
}
