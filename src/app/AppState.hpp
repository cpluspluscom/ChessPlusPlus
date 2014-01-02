#ifndef ChessPlusPlus_App_ApplicationStateBaseClass_HeaderPlusPlus
#define ChessPlusPlus_App_ApplicationStateBaseClass_HeaderPlusPlus

#include "SFML.hpp"
#include "SfmlEventHandler.hpp"

namespace chesspp
{
    namespace app
    {
        //Pure virtual abstract base class for game state management
        class AppState : public virtual SfmlEventHandler
        {
        public:
            AppState(sf::RenderWindow &disp)
            : display(disp) //cannot use {}
            {
            }

            virtual void onRender() = 0;

        protected:
            sf::RenderWindow &display;
        };
    }
}

#endif
