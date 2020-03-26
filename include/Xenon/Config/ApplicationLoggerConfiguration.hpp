#pragma once

#include <string>

namespace Xenon
{
    struct ConsoleLoggerConfiguration
    {
        bool enabled{ false };
    };

    struct FileLoggerConfiguration
    {
        bool enabled{ false };
        bool truncate{ true };
        std::string fileName{ "Xenon.log" };
    };

    class ApplicationLoggerConfiguration
    {
    public:
        explicit ApplicationLoggerConfiguration();

        void setLabel(const std::string& label);
        void useConsoleLogger() noexcept;
        void useFileLogger(const std::string& fileName, bool truncate = true);

        [[nodiscard]] std::string getLabel() const;
        [[nodiscard]] const ConsoleLoggerConfiguration& getConsoleLoggerCfg() const;
        [[nodiscard]] const FileLoggerConfiguration& getFileLoggerCfg() const;

    private:
        std::string mClientLabel{ "Client" };
        ConsoleLoggerConfiguration mConsoleLoggerCfg;
        FileLoggerConfiguration mFileLoggerCfg;
    };
}
