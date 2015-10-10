#ifndef chesspp_Exception_HeaderPlusPlus
#define chesspp_Exception_HeaderPlusPlus

#include "util/Utilities.hpp"

#include <string>
#include <exception>

namespace chesspp
{
    /**
     * \brief
     * The base exception class for all ChessPlusPlus exceptions.
     */
    class Exception
    : public virtual std::exception
    {
        std::string e; //message

    public:
        /**
         * \brief
         * Construct an exception with an optional message.
         * 
         * \param e_ optional message of exception.
         */
        Exception(std::string const &e_ = "") noexcept(noexcept(std::string(std::string(""))))
        : e{e_}
        {
        }
        Exception(Exception const &) = default;
        Exception(Exception &&) = default;
        Exception &operator=(Exception const &) = default;
        Exception &operator=(Exception &&) = default;
        virtual ~Exception() = default;

        /**
         * \brief
         * Compares two exceptions by their memory address.
         */
        virtual bool operator==(std::exception const &other) const noexcept
        {
            return &other == this;
        }
        /**
         * \brief
         * Compares two exceptions by their memory address.
         */
        friend bool operator==(std::exception const &e1, Exception const &e2) noexcept
        {
            return e2 == e1; //calls above operator==
        }

        /**
         * \brief
         * Returns the message of the exception.
         * 
         * \return The message of the exception.
         */
        virtual const char *what() const noexcept override
        {
            return e.c_str();
        }
        /**
         * \brief
         * Returns the message of the exception.
         * 
         * \return The message of the exception.
         */
        virtual operator std::string() const noexcept
        {
            return e;
        }
    };
}

#endif
