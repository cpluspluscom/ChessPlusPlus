#ifndef _APPSTATEGAME_H
	#define _APPSTATEGAME_H
#include <SFML.hpp>
#include "TextureManager.h"
#include "AppState.h"

#ifdef _DEBUG
	#include <iostream>
	using std::cout; using std::cin; using std::endl;
#endif

class AppStateGame : public AppState
{
public:
	AppStateGame(const AppStateGame&);
	AppStateGame() {cout << "in ctor" << endl;}
	~AppStateGame() {cout << "in dtor" << endl;}

	static AppStateGame *getInstance() //singleton class
	{
		static AppStateGame instance;
		return &instance;
	}

	void onActivate();
	void onEvent(sf::Event *Event);
	void onLoop();
	void onRender(sf::RenderWindow *display);
	void onDeactivate();

	//Event handler example. SFLMEvent interface redirects certain events into function calls.
	virtual void OnLButtonPressed(int x, int y);

private:
	//members of game can go here, board, etc etc.
};
#endif