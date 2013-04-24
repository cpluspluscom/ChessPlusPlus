#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <string>
#include <exception>
#include <typeinfo>

#include "util/Utilities.hpp"

namespace chesspp
{
    class Exception : public std::exception
    {
        std::string e; //message
        std::exception const&by; //caused by other exception, == *this otherwise

    public:
        Exception(std::string const&e = "") noexcept(noexcept(std::string(std::string(""))))
        : e(e), by(*this) //ignore benign warning about use of *this
        {
        }
        Exception(std::string const&e, std::exception const&by) noexcept(noexcept(std::string(std::string(""))))
        : e(e), by(by)
        {
        }
        Exception(Exception const&) = default;
        Exception(Exception &&) noexcept = default;
        Exception &operator=(Exception const&) = default;
        Exception &operator=(Exception &&) = default;
        virtual ~Exception() noexcept = default;

        virtual bool operator==(std::exception const&other) const noexcept
        {
            return dynamic_cast<Exception const*>(&other) == this;
        }
        friend bool operator==(std::exception const&e1, Exception const&e2) noexcept
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
        virtual std::exception const&cause() const noexcept
        {
            return by;
        }
        std::string fullMessage() const noexcept
        {
            std::string full = std::string(typeid(*this).name()) + " (::chespp::Exception): message = {" + e + "}";
            if(by != *this)
            {
                full += ", caused by {";
                if(typeid(by) == typeid(Exception))
                {
                    full += dynamic_cast<Exception const&>(by).fullMessage();
                }
                else
                {
                    full += by.what();
                }
                full += "}";
            }
            return full;
        }
    };
}

#endif
