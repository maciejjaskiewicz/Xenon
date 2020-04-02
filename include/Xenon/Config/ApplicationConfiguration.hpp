#pragma once

#include "ApplicationLoggerConfiguration.hpp"
#include "ApplicationWindowConfiguration.hpp"
#include "ApplicationGuiConfiguration.hpp"

namespace Xenon
{
    struct ApplicationConfiguration
    {
        ApplicationLoggerConfiguration loggerConfiguration{};
        ApplicationWindowConfiguration windowConfiguration{};
        ApplicationGuiConfiguration guiConfiguration{};
    };
}
