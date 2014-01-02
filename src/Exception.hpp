#ifndef ChessPlusPlus_ExceptionClass_HeaderPlusPlus
#define ChessPlusPlus_ExceptionClass_HeaderPlusPlus

#include "util/Utilities.hpp"

#include <string>
#include <exception>

namespace chesspp
{
    class Exception : public virtual std::exception
    {
        std::string e; //message

    public:
        Exception(std::string const &e_ = "") noexcept(noexcept(std::string(std::string(""))))
        : e{e_}
        {
        }
        Exception(Exception const &) = default;
        Exception(Exception &&) = default;
        Exception &operator=(Exception const &) = default;
        Exception &operator=(Exception &&) = default;
        virtual ~Exception() = default;

        virtual bool operator==(std::exception const &other) const noexcept
        {
            return &other == this;
        }
        friend bool operator==(std::exception const &e1, Exception const &e2) noexcept
        {
            return e2 == e1; //calls above operator==
        }

        virtual const char *what() const noexcept override
        {
            return e.c_str();
        }
        virtual operator std::string() const noexcept
        {
            return e;
        }
    };
}

#endif
