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
#include <algorithm>

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
                using Position_t = Board::Position_t;

                Board &board; //The board this piece belongs to
            private:
                Position_t p;
                Suit s;
                std::size_t movenum = 0;
            public:
                //const aliases
                Position_t const &pos = p;          //The position on the board this piece is
                Suit const &suit = s;               //Which suit the chess piece is
                std::size_t const &moves = movenum; //Current move number/number of moves made

                Piece(Board &b, Position_t const &pos, Suit const &s);
                virtual ~Piece() = default;

                virtual config::BoardConfig::Textures_t::mapped_type::mapped_type const &texture() const = 0;

                //non-virtual, calls calcTrajectory(), which should call addTrajectory() for each possible tile
                void makeTrajectory()
                {
                    addCapturable(pos);
                    calcTrajectory();
                }

                friend bool operator==(std::unique_ptr<Piece> const &up, Piece const *p) noexcept(noexcept(up.get() == p))
                {
                    return up.get() == p;
                }

                auto self() const -> std::set<std::unique_ptr<Piece>>::iterator
                {
                    return std::find(std::begin(board.pieces), std::end(board.pieces), this);
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
                        board.trajectories.insert(Board::Movements_t::value_type(self(), tile));
                    }
                }
                //further deriving classes can call this to remove a trajectory calculated by their parent class
                void removeTrajectory(Position_t const &tile)
                {
                    auto range = board.trajectories.equal_range(self());
                    for(auto it = range.first; it != range.second; )
                    {
                        if(it->second == tile)
                        {
                            it = board.trajectories.erase(it);
                        }
                        else ++it;
                    }
                }

                //deriving classes should call this from makeTrajectory to add a calculated capturable tile
                void addCapturing(Position_t const &tile)
                {
                    if(board.valid(tile))
                    {
                        board.capturings.insert(Board::Movements_t::value_type(self(), tile));
                    }
                }
                //further deriving classes can call this to remove a capturable tile calculated by their parent class
                void removeCapturing(Position_t const &tile)
                {
                    auto range = board.capturings.equal_range(self());
                    for(auto it = range.first; it != range.second; )
                    {
                        if(it->second == tile)
                        {
                            it = board.capturings.erase(it);
                        }
                        else ++it;
                    }
                }

                //deriving classes should call this from makeTrajectory to add a calculated capturable tile
                void addCapturable(Position_t const &tile)
                {
                    if(board.valid(tile))
                    {
                        board.capturables.insert(Board::Movements_t::value_type(self(), tile));
                    }
                }
                //further deriving classes can call this to remove a capturable tile calculated by their parent class
                void removeCapturable(Position_t const &tile)
                {
                    auto range = board.capturables.equal_range(self());
                    for(auto it = range.first; it != range.second; )
                    {
                        if(it->second == tile)
                        {
                            it = board.capturables.erase(it);
                        }
                        else ++it;
                    }
                }

            private:
                //Called with the position of the piece that just moved
                virtual void tick(Position_t const &m)
                {
                }

                //Sets the piece position as instructed by the board and recalculates the trajectory
                void move(Position_t const &to)
                {
                    Position_t from = pos;
                    p = to;
                    moveUpdate(from, to);
                    ++movenum;
                }

                //Called by move(), reacts to being moved
                virtual void moveUpdate(Position_t const &from, Position_t const &to)
                {
                }

            public:
                friend class ::chesspp::board::Board;
                friend std::ostream &operator<<(std::ostream &os, Piece const &p)
                {
                    return os << "Piece (" << typeid(p).name() << ") " << p.suit << " at " << p.pos << " having made " << p.moves << " moves";
                }
            };

            using Pieces_t = std::set<std::unique_ptr<Piece>>;
        private:
            struct Pieces_t_iterator_compare
            {
                bool operator()(Pieces_t::iterator const &a, Pieces_t::iterator const &b)
                {
                    return *a < *b;
                }
            };
        public:
            using Movements_t = std::multimap<Pieces_t::iterator, Position_t, Pieces_t_iterator_compare>;
            using Factory_t = std::map<config::BoardConfig::PieceClass_t, std::function<Pieces_t::value_type (Board &, Position_t const &, Suit const &)>>; //Used to create new pieces

            //represents an interaction between pieces that allows for complex moves, e.g. castling
            class Interaction
            {
            public:
                Board &board;

                Interaction(Board &b)
                : board(b)
                {
                }
                virtual ~Interaction() = 0;

                //
            };
            using Interactions_t = std::map<std::type_index, std::unique_ptr<Interaction>>;

            config::BoardConfig const &config;
        private:
            Pieces_t pieces;
            Movements_t trajectories; //where pieces can go
            Movements_t capturings;   //where pieces can capture
            Movements_t capturables;  //where pieces can be captured
            Factory_t const &factory;
            Interactions_t interactions;

        public:
            Board(config::BoardConfig const &conf, Factory_t const &fact)
            : config(conf)
            , factory(fact)
            {
                for(auto const &slot : conf.initialLayout())
                {
                    pieces.emplace(factory.at(slot.second.first)(*this, slot.first, slot.second.second));
                }

                for(auto const &p : pieces)
                {
                    p->makeTrajectory();
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

            bool occupied(Position_t const &pos) const
            {
                for(auto const &p : *this)
                {
                    if(p->pos == pos)
                    {
                        return true;
                    }
                }
                return false;
            }

            Pieces_t::const_iterator begin() const
            {
                return pieces.begin();
            }
            Pieces_t::const_iterator end() const
            {
                return pieces.end();
            }

            class Movements
            {
                Movements_t const &m;
                Movements(Movements_t const &m_)
                : m(m_)
                {
                }
                Movements(Movements const &) = delete;
                Movements(Movements &&) = delete;
                Movements &operator=(Movements const &) = delete;
                Movements &operator=(Movements &&) = delete;
                ~Movements() = default;
                friend class ::chesspp::board::Board;

            public:
                Movements_t::const_iterator begin() const
                {
                    return m.cbegin();
                }
                Movements_t::const_iterator end() const
                {
                    return m.cend();
                }
            };
        private:
            Movements const trajs {trajectories};
            Movements const captings {capturings};
            Movements const captables {capturables};
        public:
            Movements const &pieceTrajectories() const
            {
                return trajs;
            }
            Movements const &pieceCapturings() const
            {
                return captings;
            }
            Movements const &pieceCapturables() const
            {
                return captables;
            }
            class MovementsRange
            {
                std::pair<Movements_t::iterator, Movements_t::iterator> r;
                MovementsRange(std::pair<Movements_t::iterator, Movements_t::iterator> const &r_)
                : r(r_)
                {
                }
                MovementsRange(MovementsRange const &) = default;
                MovementsRange(MovementsRange &&) = default;
                MovementsRange &operator=(MovementsRange const &) = default;
                MovementsRange &operator=(MovementsRange &&) = default;
                ~MovementsRange() = default;
                friend class ::chesspp::board::Board;

            public:
                Movements_t::const_iterator begin() const
                {
                    return r.first;
                }
                Movements_t::const_iterator end() const
                {
                    return r.second;
                }
            };
            MovementsRange pieceTrajectory(Piece const &p)
            {
                return trajectories.equal_range(p.self());
            }
            MovementsRange pieceCapturing(Piece const &p)
            {
                return capturings.equal_range(p.self());
            }
            MovementsRange pieceCapturable(Piece const &p)
            {
                return capturables.equal_range(p.self());
            }

        private:
            void update(Position_t const &pos);
        public:
            //Capture a capturable piece
            bool capture(Pieces_t::iterator source, Movements_t::const_iterator target, Movements_t::const_iterator capturable);
            //Move a piece without capturing
            bool move(Pieces_t::iterator source, Movements_t::const_iterator target);

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
