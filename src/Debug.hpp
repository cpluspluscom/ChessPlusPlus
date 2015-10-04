#ifndef chesspp_Debug_HeaderPlusPlus
#define chesspp_Debug_HeaderPlusPlus

namespace chesspp
{
    /**
     * \brief
     * Redirects std::clog, std::cerr, and std::cout to individual files, permanently.
     * 
     * Calling this more than once is harmless and has no effect.
     */
    void enableRedirection() noexcept;
}

#endif
