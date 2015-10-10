#ifndef chesspp_util_Utilities_HeaderPlusPlus
#define chesspp_util_Utilities_HeaderPlusPlus

#include <type_traits>
#include <memory>
#include <iterator>
#include <utility>
#include <sstream>

namespace chesspp
{
    inline namespace util_ops
    {
        /**
         * Alternative global operator!=.
         * Smarter template than the one in ::std::rel_ops,
         * supports inheritance and non-bool return type.
         * \tparam T the left-hand type.
         * \tparam U the right-hand type.
         * \param t the left-hand value.
         * \param u the right-hand value.
         * \return !(t == u)
         */
        template<typename T, typename U>
        auto operator!=(T const &t, U const &u) noexcept(noexcept(!(t == u)))
        -> typename std::enable_if
        <
            std::is_base_of<T, U>::value
         || std::is_base_of<U, T>::value,
            decltype(!(t == u))
        >::type
        {
            return !(t == u);
        }
        /**
         * Allows comparison of std::unique_ptr and pointer.
         * \tparam T the type that std::unique_ptr wraps
         * \param up the std::unique_ptr
         * \param p the pointer
         */
        template<typename T>
        bool operator==(std::unique_ptr<T> const &up, T const *p) noexcept(noexcept(up.get() == p))
        {
            return up.get() == p;
        }
        /**
         * Allows comparison of std::unique_ptr and pointer.
         * \tparam T the type that std::unique_ptr wraps
         * \param p the pointer
         * \param up the std::unique_ptr
         */
        template<typename T>
        bool operator==(T const *p, std::unique_ptr<T> const &up) noexcept(noexcept(p == up.get()))
        {
            return p == up.get();
        }
    }
    namespace util
    {
        /**
         * Better version of std::make_signed that supports
         * floating point types, usage is identical.
         * \tparam T must be scalar.
         */
        template<typename T>
        struct MakeSigned final
        {
            static_assert(std::is_scalar<T>::value, "Template parameter must be a scalar type");
            /**
             * The signed variant of T, or T if T is floating point.
             */
            using type =
                typename std::conditional
                <
                    std::is_floating_point<T>::value,
                    std::common_type<T>,
                    std::make_signed<T>
                >::type::type;
        };
        /**
         * Template alias to complement MakeSigned.
         * Used the same way as std::is_signed.
         * \tparam T must be scalar.
         */
        template<typename T>
        using IsSigned = typename std::is_same<T, typename MakeSigned<T>::type>/*::value*/;

        /**
         * Allows iterating over the keys of a map.
         * There does not yet exist a version for iterating
         * over the values of a map.
         * \tparam Map must be std::map<Key, Value> or equivalent container
         */
        template<typename Map>
        class KeyIter final
        : public std::iterator<std::input_iterator_tag, typename Map::value_type>
        {
            typename Map::const_iterator it;
        public:
            KeyIter(typename Map::const_iterator mapit) noexcept
            : it{mapit}
            {
            }
            KeyIter(KeyIter const &) = default;
            KeyIter(KeyIter &&) = default;
            KeyIter &operator=(KeyIter const &) = default;
            KeyIter &operator=(KeyIter &&) = default;

            KeyIter &operator++() noexcept
            {
                ++it;
                return *this;
            }
            KeyIter operator++(int) noexcept
            {
                KeyIter temp = *this;
                ++*this;
                return temp;
            }

            typename Map::key_type const &operator*() const
            {
                return it->first;
            }
            typename Map::key_type const *operator->() const
            {
                return &(it->first);
            }

            friend bool operator==(KeyIter const &a, KeyIter const &b) noexcept
            {
                return a.it == b.it;
            }
            friend bool operator!=(KeyIter const &a, KeyIter const &b) noexcept
            {
                return a.it != b.it;
            }
        };

        /**
         * Takes a std::pair of iterators (e.g. the return value
         * of some standard algorithms) and uses it for begin
         * and end member functions to be compatible with
         * std::begin, std::end, and range-based for loops.
         * \tparam ItT The iterator type, e.g. container::const_iterator
         */
        template<typename ItT>
        class Range final
        {
            std::pair<ItT, ItT> r;
        public:
            Range(std::pair<ItT, ItT> const &range) noexcept
            : r{range}
            {
            }
            ItT begin() const noexcept
            {
                return r.first;
            }
            ItT end() const noexcept
            {
                return r.second;
            }
        };
        /**
         * Takes a std::pair of iterators (e.g. the return value
         * of some standard algorithms) and constructs a Range
         * object from it as a convenience function.
         * \tparam ItT The iterator type, best if left to be deduced by the compiler.
         */
        template<typename ItT>
        auto as_range(std::pair<ItT, ItT> const &range) noexcept
        -> Range<ItT>
        {
            return range;
        }

        /**
         * Allows unpacking a template parameter pack
         * into a string path with a custom delimiter.
         * \tparam ...Args The type parameter pack.
         * \param delim The delimiter, between each arg and at the end.
         * \param ...args The template parameter pack.
         */
        template<typename... Args>
        std::string path_concat(std::string const &delim, Args const &... args);
        template<typename First, typename... Rest>
        std::string path_concat(std::string const &delim, First const &first, Rest const &... rest)
        {
            std::ostringstream oss;
            oss << first << delim << path_concat<Rest...>(delim, rest...);
            return oss.str();
        }
        template<>
        inline std::string path_concat(std::string const &delim)
        {
            return "";
        }
    }
}
namespace std //for std::begin and std::end specializations
{
    /**
     * Allows iterating over the return value of equal_range().
     * \tparam Iter the iterator type, to be decuded by the compiler.
     * \param p the return value of equal_range().
     */
    template<typename Iter, typename = typename iterator_traits<Iter>::iterator_category>
    Iter begin(pair<Iter, Iter> const &p)
    {
        return p.first;
    }
    /**
     * Allows iterating over the return value of equal_range().
     * \tparam Iter the iterator type, to be decuded by the compiler.
     * \param p the return value of equal_range().
     */
    template<typename Iter, typename = typename iterator_traits<Iter>::iterator_category>
    Iter end(pair<Iter, Iter> const &p)
    {
        return p.second;
    }
}

#endif
