#ifndef __DebuggingLoggerUtility_HeaderPlusPlus__
#define __DebuggingLoggerUtility_HeaderPlusPlus__

#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <ctime>
#include <vector>
#include <cassert>

class LogUtil_buffer : public std::streambuf
{
    bool              m_timestamp_on_next_text;
    std::ostream     &m_sink;
    std::vector<char> m_buffer;

public:
    explicit LogUtil_buffer(std::ostream &sink, std::size_t buff_sz = 256)
    : m_sink(sink)
    , m_buffer(buff_sz + 1)
    , m_timestamp_on_next_text(true)
    {
        m_sink.clear();
        char *base = &m_buffer.front();
        setp(base, base + m_buffer.size()-1); //reserve an extra char for calls to overflow
    }

private:
    //Copying disabled
    LogUtil_buffer(LogUtil_buffer const &) = delete;
    LogUtil_buffer &operator=(LogUtil_buffer const &) = delete;

    //Applies timestamps and flushes buffer
    bool timestamp_and_flush();

    //Overloaded streambuf functions
    int_type overflow(int_type ch) override;
    int      sync()                override { return timestamp_and_flush() ? 0 : -1; }

    //returns std::string containing current system time.
    std::string timestamp();
};

//LogUtil_buffer implementation ///////////////////////////////////////////////////////////////////////////////
bool LogUtil_buffer::timestamp_and_flush()
{
    std::stringstream out;
    for(char *p = pbase(), *e = pptr(); p != e; ++p)
    {
        if(*p == '\n') m_timestamp_on_next_text = true;
        else if(m_timestamp_on_next_text)
        {
            if(!std::isspace(*p)) out << timestamp();
            m_timestamp_on_next_text = false;
        }
        out << *p;
    }

    std::ptrdiff_t n = pptr() - pbase();
    pbump(-n);

    return (m_sink << out.str());
}

LogUtil_buffer::int_type LogUtil_buffer::overflow(int_type ch)
{
    if(m_sink && ch != traits_type::eof())
    {
        assert(std::less_equal<char *>()(pptr(), epptr()));
        *pptr() = ch;
        pbump(1);
        if(timestamp_and_flush())
            return ch;
    }
    return traits_type::eof();
}

std::string LogUtil_buffer::timestamp()
{
    std::time_t curr_time_raw;
    std::time(&curr_time_raw);

    std::tm *local_time = std::localtime(&curr_time_raw);

    std::stringstream time;
    time << "[" << local_time->tm_hour << ":" << local_time->tm_min << ":" << local_time->tm_sec << "] ";

    return time.str();    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogUtil //replaces std::clog, std::cerr, std::cout with file streams
{
    std::ofstream log {"debug_log.log", std::ios::out|std::ios::trunc}
                , err {"debug_err.log", std::ios::out|std::ios::trunc}
                , out {"debug_out.log", std::ios::out|std::ios::trunc};
    LogUtil_buffer logbuf {log}
                 , errbuf {err}
                 , outbuf {out};
    std::streambuf *clogbuf {log ? std::clog.rdbuf(&logbuf) : std::clog.rdbuf()}
                 , *cerrbuf {err ? std::cerr.rdbuf(&errbuf) : std::cerr.rdbuf()}
                 , *coutbuf {out ? std::cout.rdbuf(&outbuf) : std::cout.rdbuf()};
    LogUtil() noexcept
    {
    }
    LogUtil(LogUtil const &) = delete;
    LogUtil(LogUtil &&) = delete;
    LogUtil &operator=(LogUtil const &) = delete;
    LogUtil &operator=(LogUtil &&) = delete;
public:
    static void EnableRedirection() noexcept
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
