#include "Application.h"

bool Application::onInit()
{
	//initialize display and such here
	display = new sf::RenderWindow(sf::VideoMode(800, 600), "ChessPlusPlus");
	//start the first active app state (will be intro in the future)
	AppStateManager::setActiveAppState(APPSTATE_GAME);
	return true;
}

void Application::onEvent(sf::Event *Event)
{
	SFMLEvent::OnEvent(Event);
	AppStateManager::onEvent(Event);
}

void Application::onLoop()
{
	AppStateManager::onLoop();
}

void Application::onRender()
{
	AppStateManager::onRender(display); //pass display to the app state.

	display->display(); //flip the display
}

void Application::onCleanup()
{
	//cleanup things that need to be cleaned up
}

int Application::Exec()
{
	if(!onInit())
		return -1;

	sf::Event Event;
	while(running)
	{
		while(display->pollEvent(Event))
			onEvent(&Event);

		onLoop();
		onRender();
	}

	onCleanup();
	return 0;
}

void Application::OnClosed()
{
	running = false;
}


