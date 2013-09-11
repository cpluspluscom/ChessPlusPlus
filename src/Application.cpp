#include "Application.hpp"

namespace chesspp
{
    int Application::exec()
    {
        sf::Event event;
        while(running)
        {
            while(display.pollEvent(event))
            {
                onEvent(event);
            }

            state->OnRender();
            display.display();
        }

        return 0;
    }

    void Application::onEvent(sf::Event &e)
    {
        switch(e.type)
        {
        case sf::Event::Closed:
            {
                state->OnClosed();
                running = false;
                break;
            }
        case sf::Event::Resized:
            {
                state->OnResized(e.size.width, e.size.height);
                break;
            }
        case sf::Event::LostFocus:
            {
                state->OnLostFocus();
                break;
            }
        case sf::Event::GainedFocus:
            {
                state->OnGainedFocus();
                break;
            }
        case sf::Event::TextEntered:
            {
                state->OnTextEntered(e.text.unicode);
                break;
            }
        case sf::Event::KeyPressed:
            {
                state->OnKeyPressed(e.key.code, e.key.alt, e.key.control, e.key.shift, e.key.system);
                break;
            }
        case sf::Event::KeyReleased:
            {
                state->OnKeyReleased(e.key.code, e.key.alt, e.key.control, e.key.shift, e.key.system);
                break;
            }
        case sf::Event::MouseWheelMoved:
            {
                state->OnMouseWheelMoved(e.mouseWheel.delta, e.mouseWheel.x, e.mouseWheel.y);
                break;
            }
        case sf::Event::MouseButtonPressed:
            {
                switch(e.mouseButton.button)
                {
                case sf::Mouse::Left:
                    {
                        state->OnLButtonPressed(e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                case sf::Mouse::Right:
                    {
                        state->OnRButtonPressed(e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                case sf::Mouse::Middle:
                    {
                        state->OnMButtonPressed(e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                default:
                    {
                        state->OnMouseButtonPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                }
                break;
            }
        case sf::Event::MouseButtonReleased:
            {
                switch(e.mouseButton.button)
                {
                case sf::Mouse::Left:
                    {
                        state->OnLButtonReleased(e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                case sf::Mouse::Right:
                    {
                        state->OnRButtonReleased(e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                case sf::Mouse::Middle:
                    {
                        state->OnMButtonReleased(e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                default:
                    {
                        state->OnMouseButtonPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
                        break;
                    }
                }
                break;
            }
        case sf::Event::MouseMoved:
            {
                state->OnMouseMoved(e.mouseMove.x, e.mouseMove.y);
                break;
            }
        case sf::Event::MouseEntered:
            {
                state->OnMouseEnteredWindow();
                break;
            }
        case sf::Event::MouseLeft:
            {
                state->OnMouseLeftWindow();
                break;
            }
        case sf::Event::JoystickButtonPressed:
            {
                state->OnJoystickButtonPressed(e.joystickButton.joystickId, e.joystickButton.button);
                break;
            }
        case sf::Event::JoystickButtonReleased:
            {
                state->OnJoystickButtonReleased(e.joystickButton.joystickId, e.joystickButton.button);
                break;
            }
        case sf::Event::JoystickMoved:
            {
                state->OnJoystickMoved(e.joystickMove.joystickId, e.joystickMove.axis, e.joystickMove.position);
                break;
            }
        case sf::Event::JoystickConnected:
            {
                state->OnJoystickConnected(e.joystickConnect.joystickId);
                break;
            }
        case sf::Event::JoystickDisconnected:
            {
                state->OnJoystickDisconnected(e.joystickConnect.joystickId);
                break;
            }
		default: break;
        }
    }

}
