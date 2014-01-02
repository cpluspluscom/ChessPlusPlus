#ifndef ChessPlusPlus_Board_CastlingPieceInteraction_HeaderPlusPlus
#define ChessPlusPlus_Board_CastlingPieceInteraction_HeaderPlusPlus

#include "Board.hpp"

#include <set>

namespace chesspp
{
    namespace board
    {
        class Castling : public Board::Interaction
        {
            std::set<Piece *> slow, fast;
        public:
            Castling(Board &b)
            : Interaction{b}
            {
            }
            virtual ~Castling() = default;

            void addSlow(Piece *p)
            {
                slow.insert(p);
            }
            void removeSlow(Piece *p)
            {
                slow.erase(p);
            }

            void addFast(Piece *p)
            {
                fast.insert(p);
            }
            void removeFast(Piece *p)
            {
                fast.erase(p);
            }

            //
        };
    }
}

#endif
