#ifndef GeneralizedChessBoardClass_HeaderPlusPlus
#define GeneralizedChessBoardClass_HeaderPlusPlus

#include "util/Position.hpp"
#include "util/Utilities.hpp"

#include <map>
#include <fstream>
#include <string>
#include <memory>
#include <cstdint>

namespace chesspp
{
    namespace board
    {
        class Piece;
        class Board
        {
        public:
            //BoardSize_t can easily be changed here if we need larger than 255x255
            using BoardSize_t = std::uint8_t;
            //Position type is based on Board Size type
            using Position_t = Position<BoardSize_t>;
            //Pieces are mapped to their positions
            using Pieces_t = std::map<Position_t, std::unique_ptr<Piece>>;
        private:
            BoardSize_t xsize, ysize;
            Pieces_t pieces;
        public:

            //These two are for user interface
            //A mouse over changes the current piece (which is allowed to be OOB)
            //A mouse click on a non-OOB piece will set the selected piece
            //(These should eventually be transferred out of the board class)
            Position hoverPos;
            Position selectedPos;

            Board();
            ~Board() noexcept = default;

            // Loads the game from new_game.txt
            bool newGame(std::string const &fileName);

            // Given a Position return the corresponding pieces idx
            int posToInt(Position const &pos) const;

            // Returns true if pos is in bounds and pieces[pos] is not NULL
            bool hasPosition(Position const &pos) const;
            // Returns the Piece*at pos.  NULL if pos is out of bounds
            Piece *at(Position const &pos) const;

            // Given screen coordinates, set the currentPiece to the proper piece
            // Note that this uses magic number 80 to know how large the screen is
            void setCurrent(int screenX, int screenY);
            Piece *getCurrent() const;

            // Set the selected piece to the parameter
            // At this point, toSelect is always currentPiece
            void setSelected(Piece *toSelect);
            Piece *getSelected() const;

            // Move a piece from one place to another
            // The parameters should be changed to two Positions
            // But such a change would require Position to handle screen values
            // In a network game, The two positions would be all that is needed
            bool move(Piece *toMove, int screenX, int screenY);
        };
    }
}

#endif
