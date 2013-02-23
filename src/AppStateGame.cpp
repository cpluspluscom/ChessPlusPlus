#include "AppStateGame.h"

void AppStateGame::onRender( sf::RenderWindow *display )
{

}

void AppStateGame::onLoop()
{
	
}

void AppStateGame::onActivate()
{
#ifdef _DEBUG
		cout << "AppStateGame activated." << endl; //<--- placeholder for proof of concept
#endif // _DEBUG
}

void AppStateGame::onDeactivate()
{
#ifdef _DEBUG
		cout << "AppStateGame deactivated." << endl; //<--- placeholder for proof of concept
#endif // _DEBUG
}

void AppStateGame::OnLButtonPressed(int x, int y)
{
#ifdef _DEBUG
         cout << "Left button clicked." << endl;
#endif // _DEBUG
}
