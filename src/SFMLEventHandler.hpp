#ifndef SFMLEventHandlerBaseClass_HeaderPlusPlus
#define SFMLEventHandlerBaseClass_HeaderPlusPlus

#include "SFML.hpp"

namespace chesspp
{
    class SFMLEventHandler
    {
    public:
        using uint = unsigned int;
        virtual void OnClosed                ()                                                                       noexcept {}
        virtual void OnResized               (uint w, uint h)                                                         noexcept {}
        virtual void OnLostFocus             ()                                                                       noexcept {}
        virtual void OnGainedFocus           ()                                                                       noexcept {}
        virtual void OnTextEntered           (sf::Uint32 unicode)                                                     noexcept {}
        virtual void OnKeyPressed            (sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) noexcept {}
        virtual void OnKeyReleased           (sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) noexcept {}
        virtual void OnMouseWheelMoved       (int delta, int x, int y)                                                noexcept {}
        virtual void OnLButtonPressed        (int x, int y)                                                           noexcept {}
        virtual void OnLButtonReleased       (int x, int y)                                                           noexcept {}
        virtual void OnRButtonPressed        (int x, int y)                                                           noexcept {}
        virtual void OnRButtonReleased       (int x, int y)                                                           noexcept {}
        virtual void OnMButtonPressed        (int x, int y)                                                           noexcept {}
        virtual void OnMButtonReleased       (int x, int y)                                                           noexcept {}
        virtual void OnMouseButtonPressed    (sf::Mouse::Button button, int x, int y)                                 noexcept {}
        virtual void OnMouseButtonReleased   (sf::Mouse::Button button, int x, int y)                                 noexcept {}
        virtual void OnMouseMoved            (int x, int y)                                                           noexcept {}
        virtual void OnMouseEnteredWindow    ()                                                                       noexcept {}
        virtual void OnMouseLeftWindow       ()                                                                       noexcept {}
        virtual void OnJoystickButtonPressed (uint joystickID, uint button)                                           noexcept {}
        virtual void OnJoystickButtonReleased(uint joystickID, uint button)                                           noexcept {}
        virtual void OnJoystickMoved         (uint joystickID, sf::Joystick::Axis axis, float position)               noexcept {}
        virtual void OnJoystickConnected     (uint joystickID)                                                        noexcept {}
        virtual void OnJoystickDisconnected  (uint joystickID)                                                        noexcept {}

        virtual ~SFMLEventHandler() = default;
    };
}

#endif
