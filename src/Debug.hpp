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
#include <cctype>

/**
 * \def USE_STD_PUT_TIME
 * \brief
 * Controls whether or not to use std::put_time() or boost::posix_time::to_simple_string()
 * 
 * If not defined, the decision will be made automatically - it is known that GCC 4.9.2 and
 * below do not support std::put_time() and it is assumed that GCC 5.x will (maybe) support it.
 * 
 * You can force one or the other by defining as 1 to favor std::put_time() or 0 to favor boost.
 */
#if !defined(USE_STD_PUT_TIME)
    //GCC 4.9.2 doesn't support std::put_time yet
    #if !defined(__GNUC__) || (__GNUC__ > 4)
        #define USE_STD_PUT_TIME 1 //next version of GCC probably does
    #else
        #define USE_STD_PUT_TIME 0 //use boost alternative
        #include <boost/date_time/posix_time/posix_time.hpp>
    #endif
#endif

/**
 * \def CHESSPP_TRUNC_LOGS
 * \brief
 * Controls whether logs are truncated on each run, or appended to.
 * 
 * To append to logs on each run, do not define.
 * To truncate lots on each run, define via compiler command line.
 */
#ifdef CHESSPP_TRUNC_LOGS
    #define CHESSPP_LOG_FILE_OPEN_MODE std::ios::trunc
#else
    #define CHESSPP_LOG_FILE_OPEN_MODE std::ios::app
#endif

/**
 * \brief
 * Replaces std::clog, std::cerr, std::cout with file streams.
 * 
 * Calling enableRedirection() will permanently redirect std::clog, std::cerr, and std::cout to
 * individual files.
 */
class LogUtil
{
    class LogUtil_buffer : public std::streambuf
    {
        bool timestamp_on_next_text = true;
        std::ostream &sink;
        std::vector<char> buffer;

    public:
        explicit LogUtil_buffer(std::ostream &sink_, std::size_t buff_sz = 256)
        : sink(sink_) //can't use {}
        , buffer(buff_sz + 1) //don't use {}
        {
            sink.clear();
            char *base = &buffer.front();
            setp(base, base + buffer.size()-1); //reserve an extra char for calls to overflow
        }

    private:
        //Copying disabled
        LogUtil_buffer(LogUtil_buffer const &) = delete;
        LogUtil_buffer &operator=(LogUtil_buffer const &) = delete;

        //Applies timestamps and flushes buffer
        bool timestamp_and_flush()
        {
            std::stringstream out;
            for(char *p = pbase(), *e = pptr(); p != e; ++p)
            {
                if(*p == '\n') timestamp_on_next_text = true;
                else if(timestamp_on_next_text)
                {
                    if(!std::isspace(*p)) out << timestamp();
                    timestamp_on_next_text = false;
                }
                out << *p;
            }

            std::ptrdiff_t n = pptr() - pbase();
            pbump(-n);

            sink << out.str();
            sink.flush();
            return (!sink.fail() && !sink.bad());
        }

        //Overridden streambuf functions
        int_type overflow(int_type ch) override
        {
            if(sink && ch != traits_type::eof())
            {
                assert(std::less_equal<char *>()(pptr(), epptr()));
                *pptr() = ch;
                pbump(1);
                if(timestamp_and_flush())
                    return ch;
            }
            return traits_type::eof();
        }
        int sync() override
        {
            return timestamp_and_flush() ? 0 : -1;
        }

        //returns std::string containing current system time.
        //should eventually be updated to use std::put_time
        static std::string timestamp()
        {
            std::time_t curr_time_raw = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm *lt = std::localtime(&curr_time_raw);

            std::stringstream time;
#if USE_STD_PUT_TIME
            time << "[" << std::put_time(lt, "%H:%M:%S") << "] ";
#else
            time << "[" << boost::posix_time::to_simple_string(boost::posix_time::time_duration(lt->tm_hour, lt->tm_min, lt->tm_sec)) << "] ";
#endif
            return time.str();
        }
    };

    std::ofstream log {"debug_log.log", std::ios::out|CHESSPP_LOG_FILE_OPEN_MODE}
                , err {"debug_err.log", std::ios::out|CHESSPP_LOG_FILE_OPEN_MODE}
                , out {"debug_out.log", std::ios::out|CHESSPP_LOG_FILE_OPEN_MODE};
    LogUtil_buffer logbuf {log}
                 , errbuf {err}
                 , outbuf {out};
    std::streambuf *clogbuf {log ? std::clog.rdbuf(&logbuf) : std::clog.rdbuf()}
                 , *cerrbuf {err ? std::cerr.rdbuf(&errbuf) : std::cerr.rdbuf()}
                 , *coutbuf {out ? std::cout.rdbuf(&outbuf) : std::cout.rdbuf()};
    LogUtil()
    {
        //Force file output to appear instantly so crashes don't swallow buffered content
        logbuf.pubsetbuf(0, 0);
        errbuf.pubsetbuf(0, 0);
        outbuf.pubsetbuf(0, 0);
    }
    LogUtil(LogUtil const &) = delete;
    LogUtil(LogUtil &&) = delete;
    LogUtil &operator=(LogUtil const &) = delete;
    LogUtil &operator=(LogUtil &&) = delete;

public:
    /**
     * \brief
     * Redirects std::clog, std::cerr, and std::cout to individual files, permanently.
     * 
     * Calling this more than once is harmless and has no effect.
     */
    static void enableRedirection() noexcept
    {
        static LogUtil lu;
    }
    ~LogUtil()
    {
        std::clog.rdbuf(clogbuf), clogbuf = nullptr;
        std::cerr.rdbuf(cerrbuf), cerrbuf = nullptr;
        std::cout.rdbuf(coutbuf), coutbuf = nullptr;
    }
};

#endif
