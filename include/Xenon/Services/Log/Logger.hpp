#pragma once

#include "Xenon/Core/Api.hpp"

#include <string>
#include <memory>

namespace Xenon
{
    enum class LogSink
    {
        Console = (1 << 0),
        File = (1 << 1),
        AllAvailable = (Console | File)
    };

    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical
    };

    // Logger PIMPL
    class Logger
    {
    public:
        explicit Logger(const std::string&, LogSink = LogSink::AllAvailable);
        ~Logger();

        Logger(Logger&&) noexcept;
        Logger& operator=(Logger&&) noexcept;

        void log(LogLevel, const std::string&) const;

        void trace(const std::string&) const;
        void debug(const std::string&) const;
        void info(const std::string&) const;
        void warn(const std::string&) const;
        void error(const std::string&) const;
        void critical(const std::string&) const;

        XN_NODISCARD std::string name() const;
        XN_NODISCARD LogLevel level() const;
        void setLevel(LogLevel) const;

    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;

        friend struct Initializer;
    };

    constexpr LogSink operator|(LogSink a, LogSink b) noexcept
    {
        return static_cast<LogSink>(static_cast<int>(a) | static_cast<int>(b));
    }

    constexpr LogSink operator&(LogSink a, LogSink b) noexcept
    {
        return static_cast<LogSink>(static_cast<int>(a) & static_cast<int>(b));
    }
}