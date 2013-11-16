#ifndef ApplicationStateBaseClass_HeaderPlusPlus
#define ApplicationStateBaseClass_HeaderPlusPlus

#include "SFMLEventHandler.hpp"
#include "SFML.hpp"

namespace chesspp
{
    //Pure virtual abstract base class for game state management
    class AppState : public virtual SFMLEventHandler
    {
    public:
        AppState(sf::RenderWindow &disp)
        : display(disp)
        {
        }
        virtual ~AppState() = default;

        virtual void onRender() = 0;

    protected:
        sf::RenderWindow &display;
    };
}

#endif
