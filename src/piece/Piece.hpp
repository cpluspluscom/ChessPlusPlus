#ifndef ChessPlusPlus_Piece_ChessPieceBaseClass_HeaderPlusPlus
#define ChessPlusPlus_Piece_ChessPieceBaseClass_HeaderPlusPlus

#include "config/BoardConfig.hpp"

#include <memory>
#include <set>
#include <typeinfo>
#include <iostream>

namespace chesspp
{
    namespace board
    {
        class Board;
    }
    namespace piece
    {
        class Piece
        {
            friend class ::chesspp::board::Board;

        public:
            using Position_t = config::BoardConfig::Position_t;
            using Suit_t     = config::BoardConfig::SuitClass_t;
            using Class_t    = config::BoardConfig::PieceClass_t;

            board::Board &board;
        private:
            Position_t p;
            Suit_t s;
            Class_t c;
            std::size_t m = 0;
        public:
            Position_t  const &pos    = p;
            Suit_t      const &suit   = s;
            Class_t     const &pclass = c;
            std::size_t const &moves  = m;

            Piece(board::Board &b, Position_t const &pos, Suit_t const &s, Class_t const &pc);
            virtual ~Piece() = default;

            //non-virtual, calls calcTrajectory(), which should call addTrajectory() for each possible tile
            void makeTrajectory()
            {
                addCapturable(pos);
                calcTrajectory();
            }

        protected:
            //should call addTrajectory() for each calculated trajectory
            //and addCapture() for each possible capture
            virtual void calcTrajectory() = 0;

            //deriving classes should call this from makeTrajectory to add a calculated trajectory tile
            void addTrajectory(Position_t const &tile);
            //further deriving classes can call this to remove a trajectory calculated by their parent class
            void removeTrajectory(Position_t const &tile);

            //deriving classes should call this from makeTrajectory to add a calculated capturable tile
            void addCapturing(Position_t const &tile);
            //further deriving classes can call this to remove a capturable tile calculated by their parent class
            void removeCapturing(Position_t const &tile);

            //deriving classes should call this from makeTrajectory to add a calculated capturable tile
            void addCapturable(Position_t const &tile);
            //further deriving classes can call this to remove a capturable tile calculated by their parent class
            void removeCapturable(Position_t const &tile);

        private:
            //Called with the position of the piece that just moved
            virtual void tick(Position_t const &m)
            {
            }

            //Sets the piece position as instructed by the board
            void move(Position_t const &to)
            {
                Position_t from = pos;
                p = to;
                moveUpdate(from, to);
                ++m;
            }

            //Called by move(), reacts to being moved
            virtual void moveUpdate(Position_t const &from, Position_t const &to)
            {
            }

        public:
            friend std::ostream &operator<<(std::ostream &os, Piece const &p)
            {
                return os << "Piece (" << typeid(p).name() << ") \"" << p.suit << "\" \"" << p.pclass << "\" at " << p.pos << " having made " << p.moves << " moves";
            }
        };
    }
}

#endif
