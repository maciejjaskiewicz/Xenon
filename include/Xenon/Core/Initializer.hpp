#pragma once

#include "Api.hpp"
#include "../Services/Log/ApplicationLoggerConfiguration.hpp"
#include <memory>

namespace Xenon
{
    class Application;
}

namespace Xenon
{
    struct XN_API Initializer
    {
        inline static bool initialized = false;

        static void initialize(const ApplicationLoggerConfiguration&);
        static void registerApplication(const std::shared_ptr<Application>& application);
        static void assertIsInitialized();
    private:
        static void initializeLogging(const ApplicationLoggerConfiguration& logCfg);
    };
}
