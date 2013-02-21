#ifndef _SDLEVENT_H
	#define _SDLEVENT_H

#include <SFML.hpp>

class SFMLEvent
{
public:
	typedef unsigned int uint;
	SFMLEvent();
	virtual ~SFMLEvent();

	virtual void OnEvent(sf::Event *Event);
	virtual void OnClosed();
	virtual void OnResized(uint w, uint h);
	virtual void OnLostFocus();
	virtual void OnGainedFocus();
	virtual void OnTextEntered(UINT32 unicode);
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system);
	virtual void OnKeyReleased(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system);
	virtual void OnMouseWheelMoved(int delta, int x, int y);
	virtual void OnLButtonPressed(int x, int y);
	virtual void OnLButtonReleased(int x, int y);
	virtual void OnRButtonPressed(int x, int y);
	virtual void OnRButtonReleased(int x, int y);
	virtual void OnMButtonPressed(int x, int y);
	virtual void OnMButtonReleased(int x, int y);
	virtual void OnMouseButtonPressed(sf::Mouse::Button button, int x, int y);
	virtual void OnMouseButtonReleased(sf::Mouse::Button button, int x, int y);
	virtual void OnMouseMoved(int x, int y);
	virtual void OnMouseEnteredWindow();
	virtual void OnMouseLeftWindow();
	virtual void OnJoystickButtonPressed(uint joystickID, uint button);
	virtual void OnJoystickButtonReleased(uint joystickID, uint button);
	virtual void OnJoystickMoved(uint joystickID, sf::Joystick::Axis axis, float position);
	virtual void OnJoystickConnected(uint joystickID);
	virtual void OnJoystickDisconnected(uint joystickID);
};

#endif