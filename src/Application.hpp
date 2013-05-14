#ifndef ApplicationManagementClass_HeaderPlusPlus
#define ApplicationManagementClass_HeaderPlusPlus

#include "AppState.hpp"
#include "AppStateGame.hpp"

#include <memory>

namespace chesspp
{
    class Application
    {
        sf::RenderWindow display {sf::VideoMode(640, 640), "ChessPlusPlus", sf::Style::Close};
        bool running = true;
        std::unique_ptr<AppState> state;

        void onEvent(sf::Event &e);

    public:
        Application()
        : state(new AppStateGame(this, display))
        {
            display.setVerticalSyncEnabled(true);
        }
        ~Application() = default;

        template<class NewState, typename... ArgsT>
        void changeState(ArgsT... args)
        {
            //make sure we can create the new state first
            std::unique_ptr<NewState> temp {new NewState(args...)};
            //then swap ownership
            state.swap(temp);
            //temp properly deletes the old state at the end of its scope
        }
        int exec();
    };
}

#endif
