#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <string>
#include <exception>

#include "util/Utilities.hpp"

namespace chesspp
{
    class Exception : public std::exception
    {
        std::string e; //message

    public:
        Exception(std::string const &e = "") noexcept(noexcept(std::string(std::string(""))))
        : e(e)
        {
        }
        Exception(Exception const &) = default;
        Exception(Exception &&) noexcept = default;
        Exception &operator=(Exception const &) = default;
        Exception &operator=(Exception &&) = default;
        virtual ~Exception() noexcept = default;

        virtual bool operator==(std::exception const &other) const noexcept
        {
            return &other == this;
        }
        friend bool operator==(std::exception const &e1, Exception const &e2) noexcept
        {
            return e2 == e1; //calls above operator==
        }

        virtual const char *what() const noexcept
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
