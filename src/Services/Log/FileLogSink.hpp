#pragma once

#include "LogSink.hpp"

namespace Xenon
{
    struct FileLogSink final : IFileLogSink
    {
        explicit FileLogSink(const std::string&, bool = true);
        spdlog::sink_ptr get() override;

    private:
        spdlog::sink_ptr mSink;
    };

    struct NullFileLogSink final : IFileLogSink
    {
        explicit NullFileLogSink();
        spdlog::sink_ptr get() override;

    private:
        spdlog::sink_ptr mSink;
    };
}