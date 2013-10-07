#ifndef MiscellaneousUtilities_HeaderPlusPlus
#define MiscellaneousUtilities_HeaderPlusPlus

#include <type_traits>

namespace chesspp
{
//    //Smarter template than the one in ::std::rel_ops, supports inheritance and non-bool return type
//    template<typename T, typename U>
//    auto operator!=(T const &t, U const &u) noexcept(noexcept(!(t == u)))
//    -> typename std::enable_if<std::is_base_of<T, U>::value || std::is_base_of<U, T>::value, decltype(!(t == u))>::type
//    {
//        return !(t == u);
//    }

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
}

#endif
