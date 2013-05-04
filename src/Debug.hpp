#ifndef DebuggingLoggerUtilityClass_HeaderPlusPlus
#define DebuggingLoggerUtilityClass_HeaderPlusPlus

#include <iostream>
#include <fstream>
#include <streambuf>

class LogUtil //replaces std::clog, std::cerr, std::cout with file streams
{
    std::ofstream log {"debug_log.log", std::ios::out|std::ios::trunc}
                , err {"debug_err.log", std::ios::out|std::ios::trunc}
                , out {"debug_out.log", std::ios::out|std::ios::trunc};
    std::streambuf *clogbuf {log ? std::clog.rdbuf(log.rdbuf()) : std::clog.rdbuf()}
                 , *cerrbuf {err ? std::cerr.rdbuf(err.rdbuf()) : std::cerr.rdbuf()}
                 , *coutbuf {out ? std::cout.rdbuf(out.rdbuf()) : std::cout.rdbuf()};
    LogUtil() noexcept = default;
    LogUtil(LogUtil const &) = delete;
    LogUtil(LogUtil &&) = delete;
    LogUtil &operator=(LogUtil const &) = delete;
    LogUtil &operator=(LogUtil &&) = delete;
public:
    static void EnableRedirection() noexcept
    {
        static LogUtil lu;
    }
    ~LogUtil() noexcept
    {
        std::clog.rdbuf(clogbuf), clogbuf = nullptr;
        std::cerr.rdbuf(cerrbuf), cerrbuf = nullptr;
        std::cout.rdbuf(coutbuf), coutbuf = nullptr;
    }
};

#endif
