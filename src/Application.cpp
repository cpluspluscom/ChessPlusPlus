#include "Application.hpp"
#include <iostream>

namespace chesspp
{
    Application::Application()
    :   display(sf::VideoMode(640, 640), "ChessPlusPlus", sf::Style::Close),
        running(true),
        state(new AppStateGame(this, &display))
    {
        display.setVerticalSyncEnabled(true);
    }

    int Application::Exec()
    {
        sf::Event Event;
        while(running)
        {
            while(display.pollEvent(Event))
                OnEvent(&Event);

            state->OnRender();
            display.display();
        }

        return 0;
    }

    Application::~Application()
    {
        delete state; //Even if it's null, no matter.
    }

    void Application::OnEvent(sf::Event *Event)
    {
        switch(Event->type)
        {
        case sf::Event::Closed:
            {
                state->OnClosed();
                running = false;
                break;
            }
        case sf::Event::Resized:
            {
                state->OnResized(Event->size.width, Event->size.height);
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
                state->OnTextEntered(Event->text.unicode);
                break;
            }
        case sf::Event::KeyPressed:
            {
                state->OnKeyPressed(Event->key.code, Event->key.alt, Event->key.control, Event->key.shift, Event->key.system);
                break;
            }
        case sf::Event::KeyReleased:
            {
                state->OnKeyReleased(Event->key.code, Event->key.alt, Event->key.control, Event->key.shift, Event->key.system);
                break;
            }
        case sf::Event::MouseWheelMoved:
            {
                state->OnMouseWheelMoved(Event->mouseWheel.delta, Event->mouseWheel.x, Event->mouseWheel.y);
                break;
            }
        case sf::Event::MouseButtonPressed:
            {
                switch(Event->mouseButton.button)
                {
                case sf::Mouse::Left:
                    {
                        state->OnLButtonPressed(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Right:
                    {
                        state->OnRButtonPressed(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Middle:
                    {
                        state->OnMButtonPressed(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                default:
                    {
                        state->OnMouseButtonPressed(Event->mouseButton.button, Event->mouseButton.x, Event->mouseButton.y);
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
                        state->OnLButtonReleased(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Right:
                    {
                        state->OnRButtonReleased(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                case sf::Mouse::Middle:
                    {
                        state->OnMButtonReleased(Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                default:
                    {
                        state->OnMouseButtonPressed(Event->mouseButton.button, Event->mouseButton.x, Event->mouseButton.y);
                        break;
                    }
                }
                break;
            }
        case sf::Event::MouseMoved:
            {
                state->OnMouseMoved(Event->mouseMove.x, Event->mouseMove.y);
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
                state->OnJoystickButtonPressed(Event->joystickButton.joystickId, Event->joystickButton.button);
                break;
            }
        case sf::Event::JoystickButtonReleased:
            {
                state->OnJoystickButtonReleased(Event->joystickButton.joystickId, Event->joystickButton.button);
                break;
            }
        case sf::Event::JoystickMoved:
            {
                state->OnJoystickMoved(Event->joystickMove.joystickId, Event->joystickMove.axis, Event->joystickMove.position);
                break;
            }
        case sf::Event::JoystickConnected:
            {
                state->OnJoystickConnected(Event->joystickConnect.joystickId);
                break;
            }
        case sf::Event::JoystickDisconnected:
            {
                state->OnJoystickDisconnected(Event->joystickConnect.joystickId);
                break;
            }
        default:
            break;
        }
    }

}
