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

    std::string ApplicationLoggerConfiguration::getLabel() const
    {
        return mClientLabel;
    }

    [[nodiscard]] const ConsoleLoggerConfiguration& ApplicationLoggerConfiguration::getConsoleLoggerCfg() const
    {
        return mConsoleLoggerCfg;
    }

    [[nodiscard]] const FileLoggerConfiguration& ApplicationLoggerConfiguration::getFileLoggerCfg() const
    {
        return mFileLoggerCfg;
    }
}