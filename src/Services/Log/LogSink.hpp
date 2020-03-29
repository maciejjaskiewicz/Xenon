#pragma once

#include <spdlog/spdlog.h>
#include <string>

namespace Xenon
{
    static const std::string LOGGER_SINK_PATTERN = "[%T.%e][%n]%^[%l]%$ %v";

    struct ILogSink
    {
        virtual ~ILogSink() = default;
        virtual spdlog::sink_ptr get() = 0;
    };

    struct IConsoleLogSink : ILogSink
    {
        virtual ~IConsoleLogSink() = default;
    };

    struct IFileLogSink : ILogSink
    {
        virtual ~IFileLogSink() = default;
    };
}