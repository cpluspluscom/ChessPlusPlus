#ifndef LOWPIECE_H
#define LOWPIECE_H

// Warnings:
//    Changing the dimensions or layout of the piece texture (the actual png)
//    will break the use of a piece and it's derived classes
// Notes:
//    A piece's color determines what part of the texture it belongs to:
//      textureX = givenValX
//      textureY = givenValY + ( this->color == WHITE ? 0 : 80 )

// The contigousness of this container does not matter
// It could be sorted for std::lower_bound?  I don't think time is an issue
#include <vector>
#include "Position.hpp"

namespace chesspp
{
    namespace board
    {
        class Board;
        typedef std::vector<Position> posList;

        enum Color
        {
            WHITE = 0,
            BLACK
        };
        enum Type
        {
            PAWN = 0,
            ROOK,
            KNIGHT,
            BISHOP,
            QUEEN,
            KING
        };

        class Piece
        {
        private:
            Position texturePos;   // Where in the texture is this piece? (hardcoded)
            Color const color;     // What color is this piece (WHITE, BLACK)
            Type const type;       // What type this piece is.

        protected:

            posList trajectory;    // The list of possible Positions (see OnValidity.txt)
            Position boardPos;     // The position on the baord this piece is

        public:

            Piece(Position const &bPos, Position const &tPos, Color c, Type t);
            virtual ~Piece() = default; 

            // Standard Accesors
            const Position&getBoardPos() const;
            const Position&getTexturePos() const;
            Color getColor() const;
            Type getType() const;
            const posList&getTrajectory() const;

            // We need to know these things :)
            // If a piece moves, it's trajectory needs to be checked for a king
            // If the king moves, the trajectory of a Pawn is a little different
            // A pawn thinks the position ahead of it is valid
            // Kings don't like to move into an enemy's valid position
            // The converse for the pawn's diagonal
            virtual bool isPawn();
            virtual bool isKing();

            // Make pure virtual when all pieces have the function
            virtual void makeTrajectory(Board const *board)
            {
            }

            // Used by Queen, Bishop, and Rook
            // This function moves in Direction d until the end of the board
            // These Positions are added to the piece's trajectory
            void shootPath(Board const *board, Direction const d);

            // This function is called for every piece after a piece moves
            // If the two Positions are in the piece's trajectory
            // Then makeTrajectory is called (makeTrajectory starts from scratch)
            // Maybe there is a better way to do it ?
            // Knights would be easy, would have to do virtual
            void updateTrajectory(Board const *board, Position const &old, Position const &knew);

            // Moves the piece.  Most pieces use this/
            // As of now, only Pawns do not because pawns have a "firstMove"
            // Kings would also need to override this
            virtual bool move(Position const &moveTo);

            friend std::ostream &operator<<(std::ostream &out, Piece const &p);
        };
    }
}

// This is handy, thanks.
#include "Board.hpp"

#endif
