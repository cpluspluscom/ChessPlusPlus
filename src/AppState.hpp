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
        
        enum class States : int {CURRENTSTATE = 0, STARTMENUSTATE = 1, CHESSPLUSPLUSSTATE = 2};
        
        virtual States stateChange() { return destState; }

    protected:
        sf::RenderWindow &display;
        States destState;
    };
}

#endif
