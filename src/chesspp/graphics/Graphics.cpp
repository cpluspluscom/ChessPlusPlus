#include "Graphics.hpp"

namespace chesspp
{
    namespace graphics
    {
        GraphicsHandler::GraphicsHandler( sf::RenderWindow *_display ) : display(_display)
        {
            try 
            {
                config::BoardConfig boardConfig;
                config::GraphicsConfig graphicsConfig;

                board = sf::Sprite(TextureManager::getInstance().Load(graphicsConfig.getSpritePath_board()));
                pieces = sf::Sprite(TextureManager::getInstance().Load(graphicsConfig.getSpritePath_pieces()));
                validMove = sf::Sprite(TextureManager::getInstance().Load(graphicsConfig.getSpritePath_validMove()));

                cell_size = boardConfig.getCellWidth();
            }
            catch(Exception &e) 
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
        void GraphicsHandler::drawPiece(board::Piece *p)
        {
            pieces.setTextureRect(sf::IntRect(p->getType()*cell_size, p->getColor()*cell_size, cell_size, cell_size));
            drawSpriteAtCell(pieces, p->getBoardPos().getX(), p->getBoardPos().getY());
        }
        void GraphicsHandler::drawPieceAt(board::Piece *p, const sf::Vector2i &pos)
        {
            pieces.setTextureRect(sf::IntRect(p->getType()*cell_size, p->getColor()*cell_size, cell_size, cell_size));
            pieces.setPosition(pos.x - (cell_size / 2), pos.y - (cell_size / 2));

            display->draw(pieces);
        }
        void GraphicsHandler::drawValidMove(const int x, const int y)
        {
            drawSpriteAtCell(validMove, x, y);
        }
        void GraphicsHandler::drawBoard(const board::Board *b)
        {
            drawBackground();

            // Valid moves are drawn for the piece being hovered over
            // Or the piece that is currently selected
            board::Piece* pCurrent = b->getCurrent();
            board::Piece* pSelect  = b->getSelected();
            if (pSelect)
                for (auto &i: pSelect->getTrajectory())
                {
                    if(i.isValid())
                        drawValidMove(i.getX(), i.getY());
                }
            else if (pCurrent)
                for (auto &i: pCurrent->getTrajectory())
                {
                    if(i.isValid())
                        drawValidMove(i.getX(), i.getY());
                }

            // Draw the non-selected pieces
            for(auto &i: b->pieces)
            {
                if(i && i != b->getSelected())
                    drawPiece(i);
            }

            // Draw the selected piece
            if (b->getSelected())
                drawPieceAt(b->getSelected(), sf::Mouse::getPosition(*display));
        }
    }
}
