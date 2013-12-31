#include "Debug.hpp"


LogUtil::LogUtil_buffer::LogUtil_buffer(std::ostream &sink_, std::size_t buff_sz )
: sink(sink_)
, buffer(buff_sz + 1)
{
    sink.clear();
    char *base = &buffer.front();
    setp(base, base + buffer.size()-1); //reserve an extra char for calls to overflow
}

bool LogUtil::LogUtil_buffer::timestamp_and_flush()
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

LogUtil::LogUtil_buffer::int_type LogUtil::LogUtil_buffer::overflow(int_type ch)
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
int LogUtil::LogUtil_buffer::sync()
{
    return timestamp_and_flush() ? 0 : -1;
}

std::string LogUtil::LogUtil_buffer::timestamp()
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

void LogUtil::enableRedirection()
{
    static LogUtil lu;
}
LogUtil::~LogUtil()
{
    std::clog.rdbuf(clogbuf), clogbuf = nullptr;
    std::cerr.rdbuf(cerrbuf), cerrbuf = nullptr;
    std::cout.rdbuf(coutbuf), coutbuf = nullptr;
}
