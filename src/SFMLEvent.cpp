#include "SFMLEvent.h"

namespace chesspp
{
    SFMLEvent::SFMLEvent()
    {
    }

    SFMLEvent::~SFMLEvent()
    {
    }

    void SFMLEvent::OnEvent(sf::Event *Event)
    {
        switch(Event->type)
        {
        case sf::Event::Closed:
            {
                OnClosed();
                break;
            }
        case sf::Event::Resized:
            {
                OnResized(Event->size.width, Event->size.height);
                break;
            }
        case sf::Event::LostFocus:
            {
                OnLostFocus();
                break;
            }
        case sf::Event::GainedFocus:
            {
                OnGainedFocus();
                break;
            }
        case sf::Event::TextEntered:
            {
                OnTextEntered(Event->text.unicode);
                break;
            }
        case sf::Event::KeyPressed:
            {
                OnKeyPressed(Event->key.code, Event->key.alt, Event->key.control, Event->key.shift, Event->key.system);
                break;
            }
        case sf::Event::KeyReleased:
            {
                OnKeyReleased(Event->key.code, Event->key.alt, Event->key.control, Event->key.shift, Event->key.system);
                break;
            }
        case sf::Event::MouseWheelMoved:
            {
                OnMouseWheelMoved(Event->mouseWheel.delta, Event->mouseWheel.x, Event->mouseWheel.y);
                break;
            }
        case sf::Event::MouseButtonPressed:
            {
                switch(Event->mouseButton.button)
                {
                case sf::Mouse::Left:
                    {
                        OnLButtonPressed(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Right:
                    {
                        OnRButtonPressed(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Middle:
                    {
                        OnMButtonPressed(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                default:
                    {
                        OnMouseButtonPressed(Event->mouseButton.button, Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                }
                break;
            }
        case sf::Event::MouseButtonReleased:
            {
                switch(Event->mouseButton.button)
                {
                case sf::Mouse::Left:
                    {
                        OnLButtonReleased(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Right:
                    {
                        OnRButtonReleased(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Middle:
                    {
                        OnMButtonReleased(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                default:
                    {
                        OnMouseButtonPressed(Event->mouseButton.button, Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                }
                break;
            }
        case sf::Event::MouseMoved:
            {
                OnMouseMoved(Event->mouseMove.x, Event->mouseMove.y);
                break;
            }
        case sf::Event::MouseEntered:
            {
                OnMouseEnteredWindow();
                break;
            }
        case sf::Event::MouseLeft:
            {
                OnMouseLeftWindow();
                break;
            }
        case sf::Event::JoystickButtonPressed:
            {
                OnJoystickButtonPressed(Event->joystickButton.joystickId, Event->joystickButton.button);
                break;
            }
        case sf::Event::JoystickButtonReleased:
            {
                OnJoystickButtonReleased(Event->joystickButton.joystickId, Event->joystickButton.button);
                break;
            }
        case sf::Event::JoystickMoved:
            {
                OnJoystickMoved(Event->joystickMove.joystickId, Event->joystickMove.axis, Event->joystickMove.position);
                break;
            }
        case sf::Event::JoystickConnected:
            {
                OnJoystickConnected(Event->joystickConnect.joystickId);
                break;
            }
        case sf::Event::JoystickDisconnected:
            {
                OnJoystickDisconnected(Event->joystickConnect.joystickId);
                break;
            }
        default:
            break;
        }
    }

    //pure virtual, do nothing
    void SFMLEvent::OnClosed() {
    }
    void SFMLEvent::OnResized(uint w, uint h) {
    }
    void SFMLEvent::OnLostFocus() {
    }
    void SFMLEvent::OnGainedFocus() {
    }
    void SFMLEvent::OnTextEntered(UINT32 unicode) {
    }
    void SFMLEvent::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) {
    }
    void SFMLEvent::OnKeyReleased(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) {
    }
    void SFMLEvent::OnMouseWheelMoved(int delta, int x, int y) {
    }
    void SFMLEvent::OnLButtonPressed(int x, int y) {
    }
    void SFMLEvent::OnLButtonReleased(int x, int y) {
    }
    void SFMLEvent::OnRButtonPressed(int x, int y) {
    }
    void SFMLEvent::OnRButtonReleased(int x, int y) {
    }
    void SFMLEvent::OnMButtonPressed(int x, int y) {
    }
    void SFMLEvent::OnMButtonReleased(int x, int y) {
    }
    void SFMLEvent::OnMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
    }
    void SFMLEvent::OnMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
    }
    void SFMLEvent::OnMouseMoved(int x, int y) {
    }
    void SFMLEvent::OnMouseEnteredWindow() {
    }
    void SFMLEvent::OnMouseLeftWindow() {
    }
    void SFMLEvent::OnJoystickButtonPressed(uint joystickID, uint button) {
    }
    void SFMLEvent::OnJoystickButtonReleased(uint joystickID, uint button) {
    }
    void SFMLEvent::OnJoystickMoved(uint joystickID, sf::Joystick::Axis axis, float position) {
    }
    void SFMLEvent::OnJoystickConnected(uint joystickID) {
    }
    void SFMLEvent::OnJoystickDisconnected(uint joystickID) {
    } 
}