#pragma once

#include "../Core/Api.hpp"

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

        XN_NODISCARD std::string label() const;
        XN_NODISCARD const ConsoleLoggerConfiguration& consoleLoggerCfg() const;
        XN_NODISCARD const FileLoggerConfiguration& fileLoggerCfg() const;

    private:
        std::string mClientLabel{ "Client" };
        ConsoleLoggerConfiguration mConsoleLoggerCfg;
        FileLoggerConfiguration mFileLoggerCfg;
    };
}
