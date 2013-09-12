#include <iostream>
#include <fstream>
#include <streambuf>
#include <typeinfo>

#include "Application.hpp"
#include "Debug.hpp"
#include "Exception.hpp"

int main()
{
    LogUtil::enableRedirection();

    try
    {
        return chesspp::Application().exec();
    }
    catch(std::exception &e)
    {
        std::clog << typeid(e).name() << " caught in main: " << e.what() << std::endl;
        return -1;
    }
}
