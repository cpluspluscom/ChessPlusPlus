#ifndef _APPSTATE_H
#define _APPSTATE_H
#include "SFMLEvent.h"

//pure virtual abstract base class for game state management. 
class AppState : public SFMLEvent
{
public:
	AppState() {}
	virtual ~AppState() {}

	virtual void onActivate() = 0;
	void onEvent(sf::Event *Event) { SFMLEvent::OnEvent(Event); }
	virtual void onLoop() = 0;
	virtual void onRender(sf::RenderWindow *display) = 0;
	virtual void onDeactivate() = 0;
};

#endif