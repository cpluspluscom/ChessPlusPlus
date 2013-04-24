#ifndef __Miscellaneous_Utilities_HeaderPlusPlus__
#define __Miscellaneous_Utilities_HeaderPlusPlus__

#include <type_traits>

namespace chesspp
{
    //Smarter template than the one in ::std::rel_ops, supports inheritance and non-bool return type
    template<typename T, typename U>
    auto operator!=(T const &t, U const &u) noexcept(noexcept(!(t == u)))
    -> typename std::enable_if<std::is_base_of<T, U>::value || std::is_base_of<U, T>::value, decltype(!(t == u))>::type
    {
        return !(t == u);
    }
}

#endif
