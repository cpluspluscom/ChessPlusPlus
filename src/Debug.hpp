#ifndef DebuggingLoggerUtilityClass_HeaderPlusPlus
#define DebuggingLoggerUtilityClass_HeaderPlusPlus

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <chrono>
#include <vector>
#include <cassert>

#if !defined(USE_STD_PUT_TIME)
    //GCC 4.8.1 doesn't support std::put_time yet
    #if !defined(__GNUC__) || (__GNUC__ > 4 || ((__GNUC__ == 4) && __GNUC_MINOR__ > 8))
        #define USE_STD_PUT_TIME 1 //next version of GCC probably does
    #else
        #define USE_STD_PUT_TIME 0 //use boost alternative
        #include <boost/date_time/posix_time/posix_time.hpp>
    #endif
#endif

class LogUtil //replaces std::clog, std::cerr, std::cout with file streams
{
    class LogUtil_buffer : public std::streambuf
    {
        bool timestamp_on_next_text = true;
        std::ostream &sink;
        std::vector<char> buffer;

    public:
        explicit LogUtil_buffer(std::ostream &sink_, std::size_t buff_sz = 256);

    private:
        //Copying disabled
        LogUtil_buffer(LogUtil_buffer const &) = delete;
        LogUtil_buffer &operator=(LogUtil_buffer const &) = delete;

        //Applies timestamps and flushes buffer
        bool timestamp_and_flush();

        //Overridden streambuf functions
        int_type overflow(int_type ch) override;

        int sync() override;

        //returns std::string containing current system time.
        //should eventually be updated to use std::put_time
        static std::string timestamp();

    };

    std::ofstream log {"debug_log.log", std::ios::out|std::ios::trunc}
                , err {"debug_err.log", std::ios::out|std::ios::trunc}
                , out {"debug_out.log", std::ios::out|std::ios::trunc};
    LogUtil_buffer logbuf {log}
                 , errbuf {err}
                 , outbuf {out};
    std::streambuf *clogbuf {log ? std::clog.rdbuf(&logbuf) : std::clog.rdbuf()}
                 , *cerrbuf {err ? std::cerr.rdbuf(&errbuf) : std::cerr.rdbuf()}
                 , *coutbuf {out ? std::cout.rdbuf(&outbuf) : std::cout.rdbuf()};
    LogUtil() = default;
    LogUtil(LogUtil const &) = delete;
    LogUtil(LogUtil &&) = delete;
    LogUtil &operator=(LogUtil const &) = delete;
    LogUtil &operator=(LogUtil &&) = delete;

public:

    static void enableRedirection();
    ~LogUtil();
};

#endif
