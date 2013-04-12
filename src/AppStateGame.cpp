#include "AppState.h"

namespace chesspp
{
    AppStateGame::AppStateGame( Application* _app, sf::RenderWindow *_display ) : app(_app), AppState(_display), graphics(display)
    {
        board = new Board();
        board->newGame(boardConfig.getInitialLayout());
    }

    int AppStateGame::id() { return 1; }
	
    void AppStateGame::OnRender()
    {
        graphics.drawBoard(board);
    }

    void AppStateGame::OnLButtonPressed(int x, int y)
    {
        board->setSelected(board->getCurrent()); // No matter if NULL
    } 
    void AppStateGame::OnMouseMoved(int x, int y)
    {
        board->setCurrent(x,y);
    }
    void AppStateGame::OnLButtonReleased(int x, int y)
    {
        // board knows what is selected, but I think this looks more clear
        board->move(board->getSelected(), x, y);
        board->setSelected(NULL);
    }
}