#include "ConsoleLogSink.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/null_sink.h>

namespace Xenon
{
    ConsoleLogSink::ConsoleLogSink()
    {
        mSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        mSink->set_pattern(LOGGER_SINK_PATTERN);
    }

    spdlog::sink_ptr ConsoleLogSink::get()
    {
        return mSink;
    }

    NullConsoleLogSink::NullConsoleLogSink()
    {
        mSink = std::make_shared<spdlog::sinks::null_sink_mt>();
    }

    spdlog::sink_ptr NullConsoleLogSink::get()
    {
        return mSink;
    }
}