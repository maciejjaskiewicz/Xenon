#include <Xenon/Services/Log/Logger.hpp>

#include "InternalLogger.hpp"
#include "../../Core/InternalApplicationServices.hpp"

#include <spdlog/spdlog.h>
#include <utility>
#include <vector>
#include <iostream>

namespace Xenon
{
    class Logger::Impl final : public IInternalLogger
    {
    public:

        explicit Impl(std::string name, const LogSink sinkMask = LogSink::AllAvailable)
            : mName(std::move(name)), mSinkMask(sinkMask)
        {
            auto sinks = resolveSinks();
            mLogger = std::make_shared<spdlog::logger>(mName, sinks.begin(), sinks.end());

            spdlog::register_logger(mLogger);
            mLogger->set_level(translateLevel(mLevel));
        }

        void log(const LogLevel level, const std::string& msg) const
        {
            mLogger->log(translateLevel(level), msg);
        }

        void trace(const std::string& msg) const
        {
            mLogger->trace(msg);
        }

        void debug(const std::string& msg) const
        {
            mLogger->debug(msg);
        }

        void info(const std::string& msg) const
        {
            mLogger->info(msg);
        }

        void warn(const std::string& msg) const
        {
            mLogger->warn(msg);
        }

        void error(const std::string& msg) const
        {
            mLogger->error(msg);
        }

        void critical(const std::string& msg) const
        {
            mLogger->critical(msg);
        }

        XN_NODISCARD std::string name() const
        {
            return mName;
        }

        XN_NODISCARD LogLevel level() const
        {
            return mLevel;
        }

        void setLevel(const LogLevel level)
        {
            mLevel = level;
            mLogger->set_level(translateLevel(level));
        }

        std::shared_ptr<spdlog::logger> getInternal() override
        {
            return mLogger;
        }

    private:
        std::string mName;
        LogSink mSinkMask;
        LogLevel mLevel{LogLevel::Trace};
        std::shared_ptr<spdlog::logger> mLogger;

        XN_NODISCARD std::vector<spdlog::sink_ptr> resolveSinks() const
        {
            std::vector<spdlog::sink_ptr> sinks;

            if((mSinkMask & LogSink::Console) == LogSink::Console)
            {
                sinks.push_back(InternalApplicationServices::LogSinks::Console::ref().get());
            }

            if ((mSinkMask & LogSink::File) == LogSink::File)
            {
                sinks.push_back(InternalApplicationServices::LogSinks::File::ref().get());
            }

            return sinks;
        }

        static spdlog::level::level_enum translateLevel(const LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Trace: return spdlog::level::trace;
            case LogLevel::Info: return spdlog::level::info;
            case LogLevel::Debug: return spdlog::level::debug;
            case LogLevel::Warn: return spdlog::level::warn;
            case LogLevel::Error: return spdlog::level::err;
            case LogLevel::Critical: return spdlog::level::critical;

            default: return spdlog::level::trace;
            }
        }

        friend struct Initializer;
    };

    Logger::Logger(const std::string& name, const LogSink sinkMask)
        : mImpl(new Impl(name , sinkMask))
    { }

    Logger::~Logger() = default;
    Logger::Logger(Logger&&) noexcept = default;
    Logger& Logger::operator=(Logger&&) noexcept = default;

    // Forward an operation to the implementation
    void Logger::log(const LogLevel level, const std::string& msg) const
    {
        mImpl->log(level, msg);
    }

    void Logger::trace(const std::string& msg) const
    {
        mImpl->trace(msg);
    }

    void Logger::debug(const std::string& msg) const
    {
        mImpl->debug(msg);
    }

    void Logger::info(const std::string& msg) const
    {
        mImpl->info(msg);
    }

    void Logger::warn(const std::string& msg) const
    {
        mImpl->warn(msg);
    }

    void Logger::error(const std::string& msg) const
    {
        mImpl->error(msg);
    }

    void Logger::critical(const std::string& msg) const
    {
        mImpl->critical(msg);
    }

    std::string Logger::name() const
    {
        return mImpl->name();
    }

    LogLevel Logger::level() const
    {
        return mImpl->level();
    }

    void Logger::setLevel(const LogLevel level) const
    {
        mImpl->setLevel(level);
    }
}
