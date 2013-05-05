#ifndef GeneralizedChessBoardClass_HeaderPlusPlus
#define GeneralizedChessBoardClass_HeaderPlusPlus

#include "config/BoardConfig.hpp"
#include "util/Position.hpp"
#include "util/Utilities.hpp"

#include <map>
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
            using BoardSize_t = config::BoardConfig::BoardSize_t;
            //Position type is based on Board Size type
            using Position_t = Position<BoardSize_t>;
            //Pieces are mapped to their positions
            using Pieces_t = std::map<Position_t, std::unique_ptr<Piece>>;
        private:
            BoardSize_t xsize, ysize;
            Pieces_t pieces;

        public:
            Board(config::BoardConfig &conf);
            ~Board() noexcept = default;

            //Returns a pointer to the Piece at pos, or nullptr if pos is not occupied or out of bounds
            Piece *at(Position_t const &pos) const;

            //Move a piece from one place to another
            bool move(Position_t const &source, Position_t const &target);
        };
    }
}

#endif
