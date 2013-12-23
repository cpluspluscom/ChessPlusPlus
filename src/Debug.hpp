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
        explicit LogUtil_buffer(std::ostream &sink_, std::size_t buff_sz = 256)
        : sink(sink_)
        , buffer(buff_sz + 1)
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
            time << "[" << std::put_time(lt, "%T") << "] ";
#else
            time << "[" << boost::posix_time::to_simple_string(boost::posix_time::time_duration(lt->tm_hour, lt->tm_min, lt->tm_sec)) << "] ";
#endif
            return time.str();
        }
    };

    //Would like to have a log dir also, instead of placing in build dir
    std::ofstream log {"debug_log.log", std::ios::out|std::ios::app}
                , err {"debug_err.log", std::ios::out|std::ios::app}
                , out {"debug_out.log", std::ios::out|std::ios::app};
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
    static void enableRedirection()
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
