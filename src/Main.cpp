#include <fstream>
#include <iostream>
#include <streambuf>
#include <typeinfo>

#include "app/Application.hpp"
#include "app/StartMenuState.hpp"
#include "Debug.hpp"
#include "Exception.hpp"

/**
 * \brief
 * Entry point of the application.
 * 
 * Sets up the application window and then passes control to chesspp::app::StartMenuState
 * 
 * \param nargs argument count, not used.
 * \param args arguments, not used.
 */
int main(int nargs, char const *const *args)
{
#ifdef CHESSPP_REDIRECT_OUTPUT
    LogUtil::enableRedirection();
#endif

    try
    {
        sf::RenderWindow disp
        {
            sf::VideoMode(640, 640),
            "ChessPlusPlus",
            sf::Style::Close
        };
        chesspp::app::Application app {disp};
        app.changeState<chesspp::app::StartMenuState>(std::ref(app), std::ref(disp));
        return app.execute();
    }
    catch(std::exception &e)
    {
        std::clog << typeid(e).name() << " caught in main: " << e.what() << std::endl;
        return -1;
    }
    std::clog << "Exiting normally from main" << std::endl;
}
