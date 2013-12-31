#ifndef ApplicationManagementClass_HeaderPlusPlus
#define ApplicationManagementClass_HeaderPlusPlus

#include "AppState.hpp"
#include "config/ResourcesConfig.hpp"

#include <memory>
#include <utility>

namespace chesspp
{
    class Application
    {
        config::ResourcesConfig res_config;
        sf::RenderWindow &display;
        bool running = false;
        std::unique_ptr<AppState> state;

        void onEvent(sf::Event &e);

    public:
        Application(sf::RenderWindow &disp)
        : display(disp)
        {
            display.setVerticalSyncEnabled(true);
        }
        ~Application() = default;

        template<class NewState, typename... Args>
        void changeState(Args &&... args)
        {
            //make sure we can create the new state first
            std::unique_ptr<AppState> temp {new NewState(std::forward<Args>(args)...)};
            //then swap ownership
            state.swap(temp);
            //temp properly deletes the old state at the end of its scope
        }

        int execute();
        void stop();

        config::ResourcesConfig &resourcesConfig()
        {
            return res_config;
        }
    };
}

#endif
