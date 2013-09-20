#ifndef GeneralizedChessBoardClass_HeaderPlusPlus
#define GeneralizedChessBoardClass_HeaderPlusPlus

#include "config/BoardConfig.hpp"
#include "util/Position.hpp"
#include "util/Utilities.hpp"

#include <map>
#include <set>
#include <memory>
#include <cstdint>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <iostream>

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
            using Suit = config::BoardConfig::SuitClass_t;

            class Piece
            {
            public:
                using PosList_t = std::set<Position_t>;
                using Position_t = Board::Position_t;

            private:
                Suit s;
                PosList_t traj, capt;
                Position_t p;
                std::size_t movenum = 0;
            public:
                //const aliases for deriving classes
                Suit const &suit;            //Which suit the chess piece is
                PosList_t const &trajectory; //The list of possible Positions (non-capture only)
                PosList_t const &captures;   //The list of possible Positions (captures only)
                Position_t const &pos;       //The position on the baord this piece is
                std::size_t const &moves;    //Current move number/number of moves made

                Board &board; //The board this piece belongs to

                Piece(Board &b, Position_t const &pos, Suit const &s)
                : board(b)
                , p(pos)
                , s(s)
                , suit(s)
                , trajectory(traj)
                , captures(capt)
                , pos(p)
                , moves(movenum)
                {
                    std::clog << "Creation of " << *this << std::endl;
                }
                virtual ~Piece() = default;

                virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const = 0;

                //non-virtual, calls calcTrajectory(), which should call addTrajectory() for each possible tile
                void makeTrajectory()
                {
                    traj.clear();
                    addCapturable(pos);
                    calcTrajectory();
                }
            protected:
                //should call addTrajectory() for each calculated trajectory
                //and addCapture() for each possible capture
                virtual void calcTrajectory() = 0;
                //deriving classes should call this from makeTrajectory to add a calculated trajectory tile
                void addTrajectory(Position_t const &tile)
                {
                    if(board.valid(tile))
                    {
                        traj.insert(tile);
                    }
                }
                //further deriving classes can call this to remove a trajectory calculated by their parent class
                void removeTrajectory(Position_t const &tile)
                {
                    traj.erase(tile);
                }

                //deriving classes should call this from makeTrajectory to add a calculated capturable tile
                void addCapturing(Position_t const &tile)
                {
                    if(board.valid(tile))
                    {
                        capt.insert(tile);
                    }
                }
                //further deriving classes can call this to remove a capturable tile calculated by their parent class
                void removeCapturing(Position_t const &tile)
                {
                    capt.erase(tile);
                }

                //deriving classes should call this from makeTrajectory to add a calculated capturable tile
                void addCapturable(Position_t const &tile)
                {
                    if(board.valid(tile))
                    {
                        board.captures.insert(Board::Captures_t::value_type(board.pieces.find(pos), tile));
                    }
                }
                //further deriving classes can call this to remove a capturable tile calculated by their parent class
                void removeCapturable(Position_t const &tile)
                {
                    auto range = board.captures.equal_range(board.pieces.find(pos));
                    for(auto it = range.first; it != range.second; ++it)
                    {
                        if(it->second == tile)
                        {
                            board.captures.erase(it);
                            break;
                        }
                    }
                }

            public:
                //Called with the position of the piece that just moved
                virtual void tick(Position_t const &p)
                {
                }

                //Sets the piece position as instructed by the board and recalculates the trajectory
                void move(Position_t const &to)
                {
                    Position_t from = std::move(pos);
                    p = to;
                    moveUpdate(from, to);
                    ++movenum;
                    makeTrajectory();
                }
            private: //intentionally private, not protected
                //Called by move(), reacts to being moved
                virtual void moveUpdate(Position_t const &from, Position_t const &to)
                {
                }

            public:

                friend std::ostream &operator<<(std::ostream &os, Piece const &p)
                {
                    return os << "Piece (" << typeid(p).name() << ") " << p.suit << " at " << p.pos << " having made " << p.moves << " moves";
                }
            };

            using Pieces_t = std::map<Position_t, std::unique_ptr<Piece>>; //Pieces are mapped to their positions
            struct Pieces_t_iterator_compare
            {
                bool operator()(Pieces_t::iterator const &a, Pieces_t::iterator const &b)
                {
                    return a->first < b->first;
                }
            };
            using Captures_t = std::multimap<Pieces_t::iterator, Position_t, Pieces_t_iterator_compare>; //Some pieces can be captured from different positions (e.g. en passant)
            using Factory_t = std::map<config::BoardConfig::PieceClass_t, std::function<Pieces_t::mapped_type (Board &, Position_t const &, Suit const &)>>; //Used to create new pieces

            //represents an interaction between pieces that allows for complex moves, e.g. castling
            class Interaction
            {
            public:
                Board &b;

                Interaction(Board &b)
                : b(b)
                {
                }
                virtual ~Interaction() = 0;

                //
            };
            using Interactions_t = std::map<std::type_index, std::unique_ptr<Interaction>>;

            config::BoardConfig const &config;
        private:
            Pieces_t pieces;
            Captures_t captures;
            Factory_t const &factory;
            Interactions_t interactions;

        public:
            Board(config::BoardConfig const &conf, Factory_t const &fact)
            : config(conf)
            , factory(fact)
            {
                for(auto const &slot : conf.initialLayout())
                {
                    pieces[slot.first] = factory.at(slot.second.first)(*this, slot.first, slot.second.second);
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

            template<typename InteractionT>
            InteractionT &getInteraction()
            {
                static_assert(std::is_base_of<Interaction, InteractionT>::value, "InteractionT must derive from Board::Interaction");
                auto &t = typeid(InteractionT);
                if(interactions.find(t) == interactions.end())
                {
                    interactions[t] = std::unique_ptr<Interaction>(new InteractionT(*this));
                }
                return dynamic_cast<InteractionT &>(*interactions[t]);
            }

            //Returns a pointer to the Piece at pos, or nullptr if pos is not occupied or out of bounds
            Piece *at(Position_t const &pos)
            {
                if(pieces.find(pos) == pieces.end())
                {
                    return nullptr;
                }
                return pieces[pos].get();
            }
            Piece const *at(Position_t const &pos) const
            {
                if(pieces.find(pos) == pieces.end())
                {
                    return nullptr;
                }
                return pieces.at(pos).get();
            }

            Pieces_t::const_iterator begin() const
            {
                return pieces.begin();
            }
            Pieces_t::const_iterator end() const
            {
                return pieces.end();
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

                auto &tomove = pieces[source];
                pieces[target].swap(pieces[source]); //swap positions
                captures.erase(pieces.find(source)); //reset captures for the piece
                pieces.erase(source); //remove the one that used to be at target
                tomove->move(target);

                //Update the trajectories of pieces whose trajectories contain the the old or new position
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
                return pos.isWithin(Position_t::Origin(), {config.boardWidth(), config.boardHeight()});
            }
        };

        using Suit = Board::Suit;
        using Piece = Board::Piece;

        inline Board::Interaction::~Interaction() = default;
    }
    namespace piece
    {
        using Suit = board::Suit;
        using Piece = board::Piece;
    }
}

#endif
