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
        exception() throw() {}
        virtual ~exception() throw() {};
        exception(const exception &) throw() {}

        exception(const std::string &_e) throw() : e(_e) {}
        virtual const char *what() { return e.c_str(); }

    private:
        std::string e;
    };
}

#endif
