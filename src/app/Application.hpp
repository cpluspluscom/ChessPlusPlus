#ifndef chesspp_app_Application_HeaderPlusPlus
#define chesspp_app_Application_HeaderPlusPlus

#include "AppState.hpp"
#include "config/ResourcesConfig.hpp"

#include <memory>
#include <utility>

namespace chesspp
{
    namespace app
    {
        /**
         * \brief
         * Represents the application and holds the current AppState
         */
        class Application
        {
            config::ResourcesConfig res_config;
            sf::RenderWindow &display;
            bool running = false;
            std::unique_ptr<AppState> state;

            void onEvent(sf::Event &e);

        public:
            /**
             * \brief
             * Construct from an sf::RenderWindow
             * 
             * Also calls `sf::RenderWindow::setVerticalSyncEnabled(true)`.
             * 
             * \param disp The sf::RenderWindow that will be drawn to. Must outlive this object.
             */
            Application(sf::RenderWindow &disp)
            : display(disp) //can't use {}
            {
                display.setVerticalSyncEnabled(true);
            }

            /**
             * \brief
             * Changes the current AppState by constructing a new one in place and destructing
             * the old one.
             * 
             * The old AppState instance is destructed within this function, so it must not be
             * referenced anymore.
             * 
             * \tparam NewState The type of AppState to construct.
             * \tparam Args deuced by the compiler from the parameter list.
             * \param args Arguments to pass to the constructor of NewState
             */
            template<class NewState, typename... Args>
            void changeState(Args &&... args)
            {
                //make sure we can create the new state first
                std::unique_ptr<AppState> temp {new NewState(std::forward<Args>(args)...)};
                //then swap ownership
                state.swap(temp);
                //temp properly deletes the old state at the end of its scope
            }

            /**
             * \brief
             * Begins running the application via the current AppState
             * 
             * This function blocks while the application is running. Application::stop() can be
             * called to cause this function to return.
             * 
             * \return An appropriate return value for returning from main()
             */
            int execute();
            /**
             * \brief
             * Causes execute() to stop running and return.
             */
            void stop() noexcept;

            /**
             * \brief
             * Gives access to the config::ResourcesConfig used by this Application and its
             * AppState
             * 
             * \return The config::ResourcesConfig in use.
             */
            config::ResourcesConfig &resourcesConfig() noexcept
            {
                return res_config;
            }
        };
    }
}

#endif
