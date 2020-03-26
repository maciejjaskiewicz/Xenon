#pragma once

#include "ApplicationLoggerConfiguration.hpp"
#include "ApplicationWindowConfiguration.hpp"

namespace Xenon
{
    struct ApplicationConfiguration
    {
        ApplicationLoggerConfiguration loggerConfiguration{};
        ApplicationWindowConfiguration windowConfiguration{};
    };
}
