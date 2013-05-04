#ifndef ChessPieceBaseClass_HeaderPlusPlus
#define ChessPieceBaseClass_HeaderPlusPlus

// Warnings:
//    Changing the dimensions or layout of the piece texture (the actual png)
//    will break the use of a piece and it's derived classes
// Notes:
//    A piece's color determines what part of the texture it belongs to:
//      textureX = givenValX
//      textureY = givenValY + ( this->color == WHITE ? 0 : 80 )

#include "util/Position.hpp"
#include "Board.hpp"

#include <vector>

namespace chesspp
{
    namespace board
    {
        enum Color //needs to be abstracted
        {
            WHITE = 0,
            BLACK
        };
        enum Type //needs to be abstracted
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
            Position texturePos; //Where in the texture is this piece? (hardcoded)
            Color const color;   //What color is this piece (WHITE, BLACK)
            Type const type;     //What type this piece is.

        public:
            using Position_t = Board::Position_t;
            using PosList_t = std::vector<Position_t>;
        protected:
            PosList_t trajectory; //The list of possible Positions
            Position_t boardPos;  //The position on the baord this piece is

            Board &b; //The board this piece belongs to

        public:
            Piece(Board &b, Position_t const &bPos, Position_t const &tPos, Color c, Type t);
            virtual ~Piece() = default; 

            Position_t const &getBoardPos() const;
            Position_t const &getTexturePos() const;
            Color getColor() const;
            Type getType() const;
            PosList const &getTrajectory() const;

            //This needs to be abstracted, but for now
            //we need to know these things :)
            //If a piece moves, it's trajectory needs to be checked for a king
            //If the king moves, the trajectory of a Pawn is a little different
            //A pawn thinks the position ahead of it is valid
            //Kings don't like to move into an enemy's valid position
            //The converse for the pawn's diagonal
            virtual bool isPawn() const;
            virtual bool isKing() const;

            virtual void makeTrajectory() = 0;

            //Needs to be absracted, but for now
            //Used by Queen, Bishop, and Rook
            //This function moves in Direction d until the end of the board
            //These Positions are added to the piece's trajectory
            void shootPath(Direction d);

            //This function is called for every piece after a piece moves
            //If the two Positions are in the piece's trajectory
            //Then makeTrajectory is called (makeTrajectory starts from scratch)
            //Maybe there is a better way to do it ?
            //Knights would be easy, would have to do virtual
            void updateTrajectory(Position const &old, Position const &knew);

            //Moves the piece. Most pieces use this.
            //As of now, only Pawns do not because pawns have a "firstMove"
            //Kings would also need to override this
            virtual bool move(Position const &moveTo);

            friend std::ostream &operator<<(std::ostream &out, Piece const &p);
        };
    }
}

#endif
