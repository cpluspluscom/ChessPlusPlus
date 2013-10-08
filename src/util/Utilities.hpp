#ifndef MiscellaneousUtilities_HeaderPlusPlus
#define MiscellaneousUtilities_HeaderPlusPlus

#include <type_traits>
#include <iterator>

namespace chesspp
{
    inline namespace util
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
        -> typename std::enable_if<std::is_base_of<T, U>::value || std::is_base_of<U, T>::value, decltype(!(t == u))>::type
        {
            return !(t == u);
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
        struct MakeSigned
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
        class KeyIter : public std::iterator<std::input_iterator_tag, typename Map::value_type>
        {
            typename Map::const_iterator it;
        public:
            KeyIter(typename Map::const_iterator mapit)
            : it(mapit)
            {
            }
            KeyIter(KeyIter const &) = default;
            KeyIter(KeyIter &&) = default;
            KeyIter &operator=(KeyIter const &) = default;
            KeyIter &operator=(KeyIter &&) = default;

            KeyIter &operator++()
            {
                ++it;
                return *this;
            }
            KeyIter operator++(int)
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

            friend bool operator==(KeyIter const &a, KeyIter const &b)
            {
                return a.it == b.it;
            }
        };
    }
}

#endif
