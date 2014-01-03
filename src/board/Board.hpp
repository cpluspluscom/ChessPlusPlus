#ifndef ChessPlusPlus_Board_GeneralizedChessBoardClass_HeaderPlusPlus
#define ChessPlusPlus_Board_GeneralizedChessBoardClass_HeaderPlusPlus

#include "config/BoardConfig.hpp"
#include "util/Utilities.hpp"

#include <map>
#include <set>
#include <memory>
#include <functional>
#include <typeinfo>
#include <algorithm>

namespace chesspp
{
    namespace piece
    {
        class Piece;
    }
    namespace board
    {
        class Board
        {
            friend class ::chesspp::piece::Piece;

        public:
            using BoardSize_t = config::BoardConfig::BoardSize_t;
            using Position_t = config::BoardConfig::Position_t;
            using Suit = config::BoardConfig::SuitClass_t;
            using Pieces_t = std::set<std::unique_ptr<piece::Piece>>;
        private:
            struct Pieces_t_iterator_compare
            {
                bool operator()(Pieces_t::iterator const &a, Pieces_t::iterator const &b) const
                {
                    return *a < *b;
                }
            };
        public:
            using Movements_t = std::multimap<Pieces_t::iterator, Position_t, Pieces_t_iterator_compare>;
            using Factory_t = std::map<config::BoardConfig::PieceClass_t, std::function<Pieces_t::value_type (Board &, Position_t const &, Suit const &)>>; //Used to create new pieces

            config::BoardConfig const &config;
        private:
            Pieces_t pieces;
            Movements_t trajectories; //where pieces can go
            Movements_t capturings;   //where pieces can capture
            Movements_t capturables;  //where pieces can be captured
            static Factory_t &factory()
            {
                static Factory_t f;
                return f;
            }

        public:
            Board(config::BoardConfig const &conf);

            static auto registerPieceClass(Factory_t::key_type const &type, Factory_t::mapped_type ctor)
            -> Factory_t::iterator
            {
                return factory().insert({type, ctor}).first;
            }

            bool occupied(Position_t const &pos) const noexcept;
            auto find(piece::Piece const *p) const noexcept
            -> Pieces_t::const_iterator
            {
                return std::find_if
                (
                    std::begin(pieces),
                    std::end(pieces),
                    [p](Pieces_t::value_type const &v)
                    {
                        return v.get() == p;
                    }
                );
            }

            auto begin() const noexcept
            -> Pieces_t::const_iterator
            {
                return pieces.begin();
            }
            auto end() const noexcept
            -> Pieces_t::const_iterator
            {
                return pieces.end();
            }

            class Movements
            {
                Movements_t const &m;
                Movements(Movements_t const &m_)
                : m(m_) //can't use {}
                {
                }
                Movements(Movements const &) = delete;
                Movements(Movements &&) = delete;
                Movements &operator=(Movements const &) = delete;
                Movements &operator=(Movements &&) = delete;
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
            Movements const &pieceTrajectories() const noexcept
            {
                return trajs;
            }
            Movements const &pieceCapturings() const noexcept
            {
                return captings;
            }
            Movements const &pieceCapturables() const noexcept
            {
                return captables;
            }
            using MovementsRange = util::Range<Movements_t::const_iterator>;
            MovementsRange pieceTrajectory(piece::Piece const &p) noexcept;
            MovementsRange pieceCapturing(piece::Piece const &p) noexcept;
            MovementsRange pieceCapturable(piece::Piece const &p) noexcept;

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
    }
}

#endif
