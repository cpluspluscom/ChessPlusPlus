#include "Application.hpp"

int main()
{
    try
    {
        chesspp::Application app;
        return app.Exec();
    }
    catch (chesspp::exception& ex)
    {
        std::cout << "Caught in main: " << ex.what() << '\n';
    }
    
    return 0;
}
