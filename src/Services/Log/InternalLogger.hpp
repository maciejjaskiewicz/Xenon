#pragma once

#include <spdlog/spdlog.h>
#include <memory>

class IInternalLogger
{
public:
    virtual ~IInternalLogger() = default;
    virtual std::shared_ptr<spdlog::logger> getInternal() = 0;
};