#ifndef LOWBOARD_H
#define LOWBOARD_H

#include "log/Logger.hpp"

#include "Position.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "King.hpp"

// For loading new_game.txt
#include <fstream>
#include <string>

// The container for the board
// This should stay contiguous, or at least accessable via []
#include <vector>


namespace chesspp
{
    namespace board
    {
        using PieceList = std::vector<Piece*>;

        class Board
        {
        private:

            //  Deletes all pointers and sets to NULL
            //  Also called during destruction
            void resetBoard(void);

            // Not currently used
            // The idea is to convert screenX and screenY to a valid idx
            // and then return the Piece* found int pieces[idx]
            // The code to do this is pretty simple though
            Piece* screenToPiece(int screenX, int screenY);

        public:
            // The container to hold the Piece*
            // It is 64 large, NULL pointers mean there isn't a piece there
            PieceList pieces;

            // These two are for user interface
            // A mouse over changes the current piece (which is allowed to be NULL)
            // A mouse click on a non-NULL piece will set the selected piece
            Piece* currentPiece;
            Piece* selectedPiece;

            Board(void);   // Set up the pieces
            ~Board(void);  // Delete the pointers in pieces

            // Loads the game from new_game.txt
            bool newGame(const std::string& fileName);

            // Given a Position return the corresponding pieces idx
            int posToInt(const Position& pos) const;

            // Returns true if pos is in bounds and pieces[pos] is not NULL
            bool hasPosition(const Position& pos) const;
            // Returns the Piece* at pos.  NULL if pos is out of bounds
            Piece* at(const Position& pos) const;

            // Given screen coordinates, set the currentPiece to the proper piece
            // Note that this uses magic number 80 to know how large the screen is
            void setCurrent(int screenX, int screenY);
            Piece* getCurrent(void) const;

            // Set the selected piece to the parameter
            // At this point, toSelect is always currentPiece
            void setSelected(Piece* toSelect);
            Piece* getSelected(void) const;

            // Move a piece from one place to another
            // The parameters should be changed to two Positions
            // But such a change would require Position to handle screen values
            // In a network game, The two positions would be all that is needed
            bool move(Piece* toMove, int screenX, int screenY);
        };
    }
}
#endif
