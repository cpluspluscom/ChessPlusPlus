#include "Application.hpp"

namespace chesspp
{
    namespace app
    {
        int Application::execute()
        {
            running = true;
            sf::Event event;
            while(running)
            {
                while(display.pollEvent(event))
                {
                    onEvent(event);
                }

                state->onRender();
                display.display();
            }

            return 0;
        }
        
        void Application::stop() noexcept
        {
            running = false;
        }

        void Application::onEvent(sf::Event &e)
        {
            switch(e.type)
            {
            case sf::Event::Closed:
                {
                    state->onClosed();
                    running = false;
                    break;
                }
            case sf::Event::Resized:
                {
                    state->onResized(e.size.width, e.size.height);
                    break;
                }
            case sf::Event::LostFocus:
                {
                    state->onLostFocus();
                    break;
                }
            case sf::Event::GainedFocus:
                {
                    state->onGainedFocus();
                    break;
                }
            case sf::Event::TextEntered:
                {
                    state->onTextEntered(e.text.unicode);
                    break;
                }
            case sf::Event::KeyPressed:
                {
                    state->onKeyPressed(e.key.code, e.key.alt, e.key.control, e.key.shift, e.key.system);
                    break;
                }
            case sf::Event::KeyReleased:
                {
                    state->onKeyReleased(e.key.code, e.key.alt, e.key.control, e.key.shift, e.key.system);
                    break;
                }
            case sf::Event::MouseWheelMoved:
                {
                    state->onMouseWheelMoved(e.mouseWheel.delta, e.mouseWheel.x, e.mouseWheel.y);
                    break;
                }
            case sf::Event::MouseButtonPressed:
                {
                    switch(e.mouseButton.button)
                    {
                    case sf::Mouse::Left:
                        {
                            state->onLButtonPressed(e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    case sf::Mouse::Right:
                        {
                            state->onRButtonPressed(e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    case sf::Mouse::Middle:
                        {
                            state->onMButtonPressed(e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    default:
                        {
                            state->onMouseButtonPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
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
                            state->onLButtonReleased(e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    case sf::Mouse::Right:
                        {
                            state->onRButtonReleased(e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    case sf::Mouse::Middle:
                        {
                            state->onMButtonReleased(e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    default:
                        {
                            state->onMouseButtonPressed(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
                            break;
                        }
                    }
                    break;
                }
            case sf::Event::MouseMoved:
                {
                    state->onMouseMoved(e.mouseMove.x, e.mouseMove.y);
                    break;
                }
            case sf::Event::MouseEntered:
                {
                    state->onMouseEnteredWindow();
                    break;
                }
            case sf::Event::MouseLeft:
                {
                    state->onMouseLeftWindow();
                    break;
                }
            case sf::Event::JoystickButtonPressed:
                {
                    state->onJoystickButtonPressed(e.joystickButton.joystickId, e.joystickButton.button);
                    break;
                }
            case sf::Event::JoystickButtonReleased:
                {
                    state->onJoystickButtonReleased(e.joystickButton.joystickId, e.joystickButton.button);
                    break;
                }
            case sf::Event::JoystickMoved:
                {
                    state->onJoystickMoved(e.joystickMove.joystickId, e.joystickMove.axis, e.joystickMove.position);
                    break;
                }
            case sf::Event::JoystickConnected:
                {
                    state->onJoystickConnected(e.joystickConnect.joystickId);
                    break;
                }
            case sf::Event::JoystickDisconnected:
                {
                    state->onJoystickDisconnected(e.joystickConnect.joystickId);
                    break;
                }
            default: break;
            }
        }
    }
}
