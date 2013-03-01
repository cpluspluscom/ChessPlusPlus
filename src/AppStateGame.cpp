#include "AppState.h"

const std::string FILEPATH = "C:/Users/Steve/Documents/Visual Studio 2012/Projects/ChessPlusPlus/";

namespace chesspp
{
    AppStateGame::AppStateGame( Application* _app ) : app(_app)
    {
        backgroundPath = FILEPATH + "res/img/chessboard_640x640.png";
        piecePath = FILEPATH + "res/img/chess_pieces_80x80_each.png";
        validMovePath = FILEPATH + "res/img/valid_move.png";
        std::string gamePath(FILEPATH);
        try
        {
            background = sf::Sprite(TextureManager::getInstance().Load(backgroundPath));
            pieces = sf::Sprite(TextureManager::getInstance().Load(piecePath));
            validMove = sf::Sprite(TextureManager::getInstance().Load(validMovePath));

            board = new Board();

            gamePath += "res/games/new_game.txt";
            board->newGame(gamePath);
        }
        catch (chesspp::exception e)
        {
            std::cout << "Files not loaded here are the paths:\n"
                << backgroundPath << '\n'
                << piecePath << '\n'
                << validMovePath << '\n'
                << gamePath << '\n'
                << "\nDo Not Hit Enter.  Quit the Game\n";
            std::cin.get();
        }
    }

    int AppStateGame::id() { return 1; }
	
    void AppStateGame::OnRender(sf::RenderWindow &display)
    {
        // We can't do anything with these sprites unless we declare them
        // Might as well only call load once...

        // Draw the background
        display.draw(background);


        static const int SIZE = 80;  // To Be defined somwhere

        // Valid moves are drawn for the piece being hovered over
        // Or the piece that is currently selected

        Piece* pCurrent = board->getCurrent();
        Piece* pSelect  = board->getSelected();
        if (pSelect)
        {
            for (posList::const_iterator iter = pSelect->getTrajectory().begin(); iter != pSelect->getTrajectory().end(); iter++)
            {
                if (!iter->isValid()) continue;
                validMove.setPosition(iter->getX() * SIZE, iter->getY() * SIZE);
                display.draw(validMove);
            }
        }
        else if (pCurrent)
        {
            for (posList::const_iterator iter = pCurrent->getTrajectory().begin(); iter != pCurrent->getTrajectory().end(); iter++)
            {
                if (!iter->isValid()) continue;
                validMove.setPosition(iter->getX() * SIZE, iter->getY() * SIZE);
                display.draw(validMove);
            }
        }

        // Draw the non-selected pieces
        for (auto iter = board->pieces.begin(); iter != board->pieces.end(); iter++)
        {
            if (!*iter || *iter == board->getSelected()) continue;

            pieces.setTextureRect(sf::IntRect((*iter)->getTexturePos().getX(), (*iter)->getTexturePos().getY(), SIZE, SIZE));
            pieces.setPosition((*iter)->getBoardPos().getX() * SIZE, (*iter)->getBoardPos().getY() * SIZE);
            display.draw(pieces);
        }

        // Draw the selected piece
        if (board->getSelected())
        {
            pieces.setTextureRect(sf::IntRect(board->getSelected()->getTexturePos().getX(), board->getSelected()->getTexturePos().getY(), SIZE, SIZE));
            sf::Vector2i mPos = sf::Mouse::getPosition(display);
            pieces.setPosition(mPos.x - (SIZE / 2), mPos.y - (SIZE / 2));
            display.draw(pieces);
        }
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