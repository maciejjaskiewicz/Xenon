#include "FileLogSink.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/null_sink.h>

namespace Xenon
{
    FileLogSink::FileLogSink(const std::string& filename, const bool truncate)
    {
        mSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, truncate);
        mSink->set_pattern(LOGGER_SINK_PATTERN);
    }

    spdlog::sink_ptr FileLogSink::get()
    {
        return mSink;
    }

    NullFileLogSink::NullFileLogSink()
    {
        mSink = std::make_shared<spdlog::sinks::null_sink_mt>();
    }

    spdlog::sink_ptr NullFileLogSink::get()
    {
        return mSink;
    }
}
