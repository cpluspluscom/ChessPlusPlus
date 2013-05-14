#ifndef ApplicationStateBaseClass_HeaderPlusPlus
#define ApplicationStateBaseClass_HeaderPlusPlus

#include "SFMLEventHandler.hpp"
#include "SFML.hpp"

namespace chesspp
{
    //Pure virtual abstract base class for game state management
    class AppState : public SFMLEventHandler
    {
    public:
        AppState(sf::RenderWindow &display)
        : display(display)
        {
        }
        virtual ~AppState() = default;

        virtual int id() = 0;
        virtual void OnRender() = 0;

    protected:
        sf::RenderWindow &display;
    };
}

#endif
