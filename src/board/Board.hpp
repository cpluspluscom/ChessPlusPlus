#ifndef chesspp_board_Board_HeaderPlusPlus
#define chesspp_board_Board_HeaderPlusPlus

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
        /**
        * \brief
         * Manages pieces on a chess board.
         * 
         * Can be iterated over with a range-based for-loop.
         */
        class Board
        {
        public:
            using BoardSize_t = config::BoardConfig::BoardSize_t;
            using Position_t = config::BoardConfig::Position_t;
            using Suit = config::BoardConfig::SuitClass_t;
            using Pieces_t = std::set<std::unique_ptr<piece::Piece>>;
        private:
            struct Pieces_t_const_iterator_compare
            {
                bool operator()(Pieces_t::const_iterator const &a, Pieces_t::const_iterator const &b) const
                {
                    return *a < *b;
                }
            };
        public:
            using Movements_t = std::multimap<Pieces_t::const_iterator, Position_t, Pieces_t_const_iterator_compare>;
            using Factory_t = std::map<config::BoardConfig::PieceClass_t, std::function<Pieces_t::value_type (Board &, Position_t const &, Suit const &)>>; //Used to create new pieces

            /**
             * \brief
             * The chesspp::config::BoardConfig currently in use.
             */
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
            /**
             * \brief
             * Constructs the Board from the given chesspp::config::BoardConfig
             * 
             * \param conf The BoardConfig, must outlive this instance.
             */
            Board(config::BoardConfig const &conf);

            /**
             * \brief
             * Register a new type of chess piece.
             * 
             * This should be called via assignment to a global variable in the source file of
             * the chess piece implementation.
             * 
             * \param type The unique type of the chess piece.
             * \param ctor The function used to construct new instances of the chess piece.
             * \return The registration receipt, to be stored in the global variable.
             */
            static auto registerPieceClass(Factory_t::key_type const &type, Factory_t::mapped_type ctor)
            -> Factory_t::iterator
            {
                return factory().insert({type, ctor}).first;
            }

            /**
             * \brief
             * Check if a location on the board is occupied by at least one piece.
             * 
             * \param pos The position to check.
             * \return true if at least one piece occupies the position, false otherwise.
             */
            bool occupied(Position_t const &pos) const noexcept;
            /**
             * \brief
             * Given a Piece, obtain its iterator.
             * 
             * \param p The Piece to search for.
             * \return The iterator to the piece, or the end iterator.
             */
            auto find(piece::Piece const &p) const noexcept -> Pieces_t::const_iterator;

            /**
             * \brief
             * Get the beginning iterator of the board pieces.
             */
            auto begin() const noexcept
            -> Pieces_t::const_iterator
            {
                return pieces.cbegin();
            }
            /**
             * \brief
             * Get the end iterator of the board pieces.
             */
            auto end() const noexcept
            -> Pieces_t::const_iterator
            {
                return pieces.cend();
            }

            /**
             * \brief
             * Holds the valid movements for all pieces on the board.
             * 
             * There are three different kinds of movements:
             * - Trajectory - the locations a piece can move to
             * - Capturing - the locations a piece can capture other pieces
             * - Capturable - the locations a piece can be captured by other pieces
             * 
             * This class provides a consistent interface for all three types.
             * 
             * Can be iterated over with a range-based for-loop.
             */
            class Movements
            {
                Board &b;
                Movements_t &m;
                Movements(Board &b_, Movements_t Board::*m_)
                : b(b_)     //can't use {}
                , m(b_.*m_) //can't use {}
                {
                }
                Movements(Movements const &) = delete;
                Movements(Movements &&) = delete;
                Movements &operator=(Movements const &) = delete;
                Movements &operator=(Movements &&) = delete;
                friend class ::chesspp::board::Board;

            public:
                /**
                 * \brief
                 * Get the beginning iterator of the valid movements.
                 */
                Movements_t::const_iterator begin() const
                {
                    return m.cbegin();
                }
                /**
                 * \brief
                 * Get the end iterator of the valid movements.
                 */
                Movements_t::const_iterator end() const
                {
                    return m.cend();
                }

                /**
                 * \brief
                 * Adds a valid movement.
                 */
                void add(piece::Piece const &p, Position_t const &tile);
                /**
                 * \brief
                 * Removes a valid movement.
                 */
                void remove(piece::Piece const &p, Position_t const &tile);
            };
        private:
            Movements trajs     {*this, &Board::trajectories};
            Movements captings  {*this, &Board::capturings  };
            Movements captables {*this, &Board::capturables };
        public:
            Movements const &pieceTrajectories() const noexcept { return trajs;     }
            Movements       &pieceTrajectories()       noexcept { return trajs;     }
            Movements const &pieceCapturings()   const noexcept { return captings;  }
            Movements       &pieceCapturings()         noexcept { return captings;  }
            Movements const &pieceCapturables()  const noexcept { return captables; }
            Movements       &pieceCapturables()        noexcept { return captables; }
            using MovementsRange = util::Range<Movements_t::const_iterator>;
            MovementsRange pieceTrajectory(piece::Piece const &p) noexcept;
            MovementsRange pieceCapturing(piece::Piece const &p) noexcept;
            MovementsRange pieceCapturable(piece::Piece const &p) noexcept;

        private:
            void update(Position_t const &pos);
        public:
            /**
             * \brief
             * Capture a capturable piece.
             * 
             * \param source The piece performing the capture.
             * \param target The new location of the source piece.
             * \param capturable The location being captured.
             * \return true if the capture was successful, false otherwise.
             */
            bool capture(Pieces_t::iterator source, Movements_t::const_iterator target, Movements_t::const_iterator capturable);
            /**
             * \brief
             * Move a piece without capturing.
             * 
             * \param source The piece being moved.
             * \param target The new location of the source piece.
             * \return true if the capture was successful, false otherwise.
             */
            bool move(Pieces_t::iterator source, Movements_t::const_iterator target);

            /**
             * \brief
             * Check if a position is a valid position that exists on the board.
             * 
             * \param pos The position to check for validity.
             * \return true if the position is valid, false otherwise.
             */
            bool valid(Position_t const &pos) const noexcept
            {
                return pos.isWithin(Position_t::Origin(), {config.boardWidth(), config.boardHeight()});
            }
        };
    }
}

#endif
