#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <string>

namespace chesspp
{
    class exception
    {
    protected:
	exception &operator=(const exception &) throw();
	
    public:
        exception() throw() {}
        exception(const std::string &_e) throw() : e(_e) {}
        exception(const exception &) throw() {}
        virtual ~exception() throw() {};

        virtual std::string what() const throw() {return e;}
    private:
        std::string e;
    };
}

#endif