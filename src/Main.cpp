#include <iostream>
#include <fstream>
#include <streambuf>
#include <typeinfo>

#include "Application.hpp"
#include "ChessPlusPlusState.hpp"
#include "StartMenuState.hpp"
#include "Debug.hpp"
#include "Exception.hpp"

int main()
{
    //LogUtil::enableRedirection();

    try
    {
        sf::RenderWindow disp
        {
            sf::VideoMode(640, 640),
            "ChessPlusPlus",
            sf::Style::Close
        };
        chesspp::Application app {disp};
        app.changeState<chesspp::StartMenuState>(std::ref(app), std::ref(disp));
        return app.execute();
    }
    catch(std::exception &e)
    {
        std::clog << typeid(e).name() << " caught in main: " << e.what() << std::endl;
        return -1;
    }
}
