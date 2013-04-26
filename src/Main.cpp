#include <iostream>
#include <fstream>
#include <streambuf>
#include <typeinfo>

#include "Application.hpp"
#include "Debug.hpp"
#include "Exception.hpp"

int main()
{
    LogUtil::EnableRedirection();

    try
    {
        return chesspp::Application().Exec();
    }
    catch(std::exception &e)
    {
        std::clog << typeid(e).name() << " caught in main: " << e.what() << std::endl;
        return -1;
    }
}
