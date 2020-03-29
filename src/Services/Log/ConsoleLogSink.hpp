#pragma once

#include "LogSink.hpp"

namespace Xenon
{
    struct ConsoleLogSink final : IConsoleLogSink
    {
        explicit ConsoleLogSink();
        spdlog::sink_ptr get() override;

    private:
        spdlog::sink_ptr mSink;
    };

    struct NullConsoleLogSink final : IConsoleLogSink
    {
        explicit NullConsoleLogSink();
        spdlog::sink_ptr get() override;

    private:
        spdlog::sink_ptr mSink;
    };
}