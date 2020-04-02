#include <Xenon/Config/ApplicationLoggerConfiguration.hpp>

namespace Xenon
{
    ApplicationLoggerConfiguration::ApplicationLoggerConfiguration()
    {
        mConsoleLoggerCfg = ConsoleLoggerConfiguration();
        mFileLoggerCfg = FileLoggerConfiguration();
    }

    void ApplicationLoggerConfiguration::setLabel(const std::string& label)
    {
        mClientLabel = label;
    }

    void ApplicationLoggerConfiguration::useConsoleLogger() noexcept
    {
        mConsoleLoggerCfg.enabled = true;
    }
    
    void ApplicationLoggerConfiguration::useFileLogger(const std::string& fileName, const bool truncate)
    {
        mFileLoggerCfg.enabled = true;
        mFileLoggerCfg.fileName = fileName;
        mFileLoggerCfg.truncate = truncate;
    }

    std::string ApplicationLoggerConfiguration::label() const
    {
        return mClientLabel;
    }

    XN_NODISCARD const ConsoleLoggerConfiguration& ApplicationLoggerConfiguration::consoleLoggerCfg() const
    {
        return mConsoleLoggerCfg;
    }

    XN_NODISCARD const FileLoggerConfiguration& ApplicationLoggerConfiguration::fileLoggerCfg() const
    {
        return mFileLoggerCfg;
    }
}