#ifndef GeneralizedChessBoardClass_HeaderPlusPlus
#define GeneralizedChessBoardClass_HeaderPlusPlus

#include "config/BoardConfig.hpp"
#include "util/Position.hpp"
#include "util/Utilities.hpp"

#include <map>
#include <memory>
#include <cstdint>
#include <functional>

namespace chesspp
{
    namespace board
    {
        class Board
        {
        public:
            using BoardSize_t = config::BoardConfig::BoardSize_t;
            using Position_t = config::BoardConfig::Position_t;

            //Current most-practical solution - will abstract more later
            using Suit = config::BoardCondig::SuitClass_t;

            class Piece
            {
            public:
                using PosList_t = std::set<Position_t>;

            private:
                Suit s;
                PosList_t traj;
                Position_t p;
            public:
                //const aliases for deriving classes
                Suit const &suit;            //Which suit the chess piece is
                PosList_t const &trajectory; //The list of possible Positions
                Position_t const &pos;       //The position on the baord this piece is

                Board &b; //The board this piece belongs to

                Piece(Board &b, Position_t const &pos, Suit const &s)
                : b(b)
                , p(pos)
                , s(s)
                , suit(s)
                , trajectory(traj)
                , pos(p)
                {
                    std::clog << "Creation of " << *this << std::endl;
                }
                virtual ~Piece() = default;

                //non-virtual, calls calcTrajectory(), which should call addTrajectory() for each possible tile
                void makeTrajectory()
                {
                    traj.clear();
                    calcTrajectory();
                }
            protected:
                //should call addTrajectory() for each calculated trajectory
                virtual void calcTrajectory() = 0;
                //deriving classes should call this from makeTrajectory to add a calculated trajectory tile
                void addTrajectory(Position_t const &tile)
                {
                    if(b.valid(tile))
                    {
                        traj.insert(tile);
                    }
                    else
                    {
                        std::clog << "Invalid tile " << tile << " calculated for trajectory by " << *this << std::endl;
                    }
                }
                //further deriving classes can call this to remove a trajectory calculated by their parent class
                void removeTrajectory(Position_t const &tile)
                {
                    traj.erase(tile);
                }

            public:
                //Sets the piece position as instructed by the board and recalculates the trajectory
                void move(Position_t const &to)
                {
                    Position_t from = std::move(pos);
                    pos = to;
                    moveAnimation(from, to);
                    makeTrajectory();
                }
            private: //intentionally private, not protected
                //Called by move(), plays the animation for moving
                virtual void moveAnimation(Position_t const &from, Position_t const &to) = 0;
            public:

                friend std::ostream &operator<<(std::ostream &os, Piece const &p)            
                {
                    return os << "Piece (" << typeid(p).name() << ") " << p.suit << " at " << p.pos;
                }
            };

            using Pieces_t = std::map<Position_t, std::unique_ptr<Piece>>; //Pieces are mapped to their positions
            using Factory_t = std::map<config::BoardConfig::PieceClass_t, std::function<std::unique_ptr<Piece> (Board &, Position_t const &, Suit const &)>>; //Used to create new pieces

        private:
            BoardSize_t xsize, ysize;
            Pieces_t pieces;
            Factory_t factory;

        public:
            Board(config::BoardConfig const &conf, Factory_t const &fact)
            : xsize(conf.getBoardWidth())
            , ysize(conf.getBoardHeight())
            , factory(fact)
            {
                for(auto const &slot : conf.initialLayout())
                {
                    pieces[slot.first] = fact[slot.second.first](*this, slot.first, slot.second.second);
                }

                //This can only be done when all of the pieces are on the board
                //In a real game, it should be for the suit that has just moved first
                //So the other suit can respond to things that may have cuased check
                //It should be its own function, as it is needed in move() also.
                for(auto it = pieces.begin(); it != pieces.end(); ++it)
                {
                    it->second->makeTrajectory();
                }
            }
            ~Board() = default;

            //Returns a pointer to the Piece at pos, or nullptr if pos is not occupied or out of bounds
            Piece &at(Position_t const &pos) const
            {
                if(pieces.find(pos) == pieces.end())
                {
                    return nullptr;
                }
                return pieces[pos];
            }

            //Move a piece from one place to another
            bool move(Position_t const &source, Position_t const &target)
            {
                if(pieces.find(source) == pieces.end())
                {
                    std::cerr << "source position of piece to move does not contain a piece: " << source << std::endl;
                    return false;
                }
                if(!valid(target))
                {
                    std::cerr << "target position of piece to move is out of bounds: " << target << std::endl;
                    return false;
                }

                Piece *tomove = pieces[source];
                pieces[target].swap(pieces[source]); //swap positions
                pieces.erase(source); //remove the one that used to be at target
                tomove.move(target);

                //Update the trajectories of pieces whose trajectories contain the the old oer new position
                for(auto it = pieces.begin(); it != pieces.end(); ++it)
                {
                    Piece::PosList_t const &t = it->second->trajectory;
                    if(t.find(source) != t.end() || t.find(target) != t.end()) //source or target found
                    {
                        it->second->makeTrajectory(); //update
                    }
                }

                return true;
            }

            //Check if a position is a valid position that exists on the board
            bool valid(Position_t const &pos) const noexcept
            {
                return pos.isWithin(Position_t::ORIGIN, Position_t(xsize, ysize));
            }
        };

        using Suit = Board::Suit;
        using Piece = Board::Piece;
    }
}

#endif
