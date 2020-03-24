#pragma once

#include "../Services/Log/ApplicationLoggerConfiguration.hpp"
#include <memory>

namespace Xenon
{
    class Application;
}

namespace Xenon
{
    struct Initializer
    {
        inline static bool initialized = false;

        static void initialize(const ApplicationLoggerConfiguration&);
        static void registerApplication(const std::shared_ptr<Application>& application);
        static void assertIsInitialized();
    private:
        static void initializeLogging(const ApplicationLoggerConfiguration& logCfg);
    };
}
