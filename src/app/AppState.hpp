#ifndef chesspp_app_AppState_HeaderPlusPlus
#define chesspp_app_AppState_HeaderPlusPlus

#include "SFML.hpp"
#include "SfmlEventHandler.hpp"

namespace chesspp
{
    namespace app
    {
        /**
         * \brief
         * Base class for application states.
         * 
         * See also, chesspp::app::Application
         */
        class AppState
        : public virtual SfmlEventHandler
        {
        public:
            /**
             * \brief
             * Construct bound to an sf::RenderWindow
             * 
             * \param disp The sf::RenderWindow which must outlive this object.
             */
            AppState(sf::RenderWindow &disp)
            : display(disp) //cannot use {}
            {
            }

            /**
             * \brief
             * Called to render the current state.
             * 
             * Rendering should be done to the protected display member variable.
             */
            virtual void onRender() = 0;

        protected:
            /**
             * \brief
             * The sf::RenderWindow bound at construction.
             */
            sf::RenderWindow &display;
        };
    }
}

#endif
