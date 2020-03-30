#pragma once

#include <spdlog/spdlog.h>

namespace Xenon
{
    struct Initializer;

    struct GlobalLogConfiguration
    {
        static const std::string& appLogger()
        {
            return sAppLoggerName;
        }

        static bool initialized()
        {
            return !sAppLoggerName.empty();
        }
    private:
        friend struct Initializer;
        inline static std::string sAppLoggerName{};
    };
}

#define XN_ENG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define XN_ENG_INFO(...) spdlog::info(__VA_ARGS__)
#define XN_ENG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define XN_ENG_WARN(...) spdlog::warn(__VA_ARGS__)
#define XN_ENG_ERROR(...) spdlog::error(__VA_ARGS__)
#define XN_ENG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#define XN_TRACE(...) { !Xenon::GlobalLogConfiguration::initialized() ? spdlog::trace(__VA_ARGS__) :\
    spdlog::get(Xenon::GlobalLogConfiguration::appLogger())->trace(__VA_ARGS__); }
#define XN_INFO(...) { !Xenon::GlobalLogConfiguration::initialized() ? spdlog::info(__VA_ARGS__) :\
    spdlog::get(Xenon::GlobalLogConfiguration::appLogger())->info(__VA_ARGS__); }
#define XN_DEBUG(...) { !Xenon::GlobalLogConfiguration::initialized() ? spdlog::debug(__VA_ARGS__) :\
    spdlog::get(Xenon::GlobalLogConfiguration::appLogger())->debug(__VA_ARGS__); }
#define XN_WARN(...) { !Xenon::GlobalLogConfiguration::initialized() ? spdlog::warn(__VA_ARGS__) :\
    spdlog::get(Xenon::GlobalLogConfiguration::appLogger())->warn(__VA_ARGS__); }
#define XN_ERROR(...) { !Xenon::GlobalLogConfiguration::initialized() ? spdlog::error(__VA_ARGS__) :\
    spdlog::get(Xenon::GlobalLogConfiguration::appLogger())->error(__VA_ARGS__); }
#define XN_CRITICAL(...) { !Xenon::GlobalLogConfiguration::initialized() ? spdlog::critical(__VA_ARGS__) :\
    spdlog::get(Xenon::GlobalLogConfiguration::appLogger())->critical(__VA_ARGS__); }
