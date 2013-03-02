#include "Graphics.h"

namespace chesspp
{
    namespace graphics
    {


        GraphicsHandler::GraphicsHandler( sf::RenderWindow *_display ) : display(_display), 
            backgroundPath(file_path + "res/img/chessboard_640x640.png"), // Hardcoded. Will change in the future.
            piecePath(file_path + "res/img/chess_pieces_80x80_each.png"), //
            validMovePath(file_path + "res/img/valid_move.png")           //
        {
            try 
            {
                board = sf::Sprite(TextureManager::getInstance().Load(backgroundPath));
                pieces = sf::Sprite(TextureManager::getInstance().Load(piecePath));
                validMove = sf::Sprite(TextureManager::getInstance().Load(validMovePath));
            } 
            catch (chesspp::exception &e) 
            {
#ifdef _DEBUG
                cout << "Error: " << e.what() << endl;
#endif
            }
        }

        void GraphicsHandler::drawSpriteAtCell(sf::Sprite &s, const int x, const int y)
        {
            s.setPosition(x * cell_size, y * cell_size);
            display->draw(s);
        }
        void GraphicsHandler::drawBackground()
        {
            display->draw(board);
        }
        void GraphicsHandler::drawPiece(Piece *p)
        {
            pieces.setTextureRect(sf::IntRect(p->getType()*cell_size, p->getColor()*cell_size, cell_size, cell_size));
            drawSpriteAtCell(pieces, p->getBoardPos().getX(), p->getBoardPos().getY());
        }
        void GraphicsHandler::drawPieceAt(Piece *p, const sf::Vector2i &pos)
        {
            pieces.setTextureRect(sf::IntRect(p->getType()*cell_size, p->getColor()*cell_size, cell_size, cell_size));
            pieces.setPosition(pos.x - (cell_size / 2), pos.y - (cell_size / 2));

            display->draw(pieces);
        }
        void GraphicsHandler::drawValidMove(const int x, const int y)
        {
            drawSpriteAtCell(validMove, x, y);
        }
        void GraphicsHandler::drawBoard(const Board *b)
        {
            drawBackground();

            // Valid moves are drawn for the piece being hovered over
            // Or the piece that is currently selected
            Piece* pCurrent = b->getCurrent();
            Piece* pSelect  = b->getSelected();
            if (pSelect)
                for (posList::const_iterator iter = pSelect->getTrajectory().begin(); iter != pSelect->getTrajectory().end(); iter++)
                {
                    if(!iter->isValid()) continue;
                    drawValidMove(iter->getX(), iter->getY());
                }
            else if (pCurrent)
                for (posList::const_iterator iter = pCurrent->getTrajectory().begin(); iter != pCurrent->getTrajectory().end(); iter++)
                {
                    if(!iter->isValid()) continue;
                    drawValidMove(iter->getX(), iter->getY());
                }

            // Draw the non-selected pieces
            for (auto iter = b->pieces.begin(); iter != b->pieces.end(); iter++)
            {
                if (!*iter || *iter == b->getSelected()) continue;
                drawPiece(*iter);
            }

            // Draw the selected piece
            if (b->getSelected())
                drawPieceAt(b->getSelected(), sf::Mouse::getPosition(*display));
        }
    }
}