#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <string>
#include <exception>

namespace chesspp
{
    class exception : public std::exception
    {
        using std::exception::what;
    public:
        exception() {}
        virtual ~exception() {};
        exception(const exception &) {}

        exception(const std::string &_e) : e(_e) {}
        virtual const char *what() { return e.c_str(); }

    private:
        std::string e;
    };
}

#endif
