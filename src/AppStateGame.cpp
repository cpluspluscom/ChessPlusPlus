#include "AppStateGame.h"

void AppStateGame::onEvent(sf::Event *Event)
{
	SFMLEvent::OnEvent(Event);
}

void AppStateGame::onRender( sf::RenderWindow *display )
{

}

void AppStateGame::onLoop()
{
	
}

void AppStateGame::onActivate()
{
	cout << "AppStateGame activated." << endl; //<--- placeholder for proof of concept
}

void AppStateGame::onDeactivate()
{
	cout << "AppStateGame deactivated." << endl; //<--- placeholder for proof of concept
}

void AppStateGame::OnLButtonPressed(int x, int y)
{
	cout << "Left button clicked." << endl;
}
