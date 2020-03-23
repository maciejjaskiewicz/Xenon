#include <Xenon/Core/ApplicationBuilder.hpp>

#include "ApplicationServices.hpp"

namespace Xenon
{
    template <typename TApplication>
    ApplicationBuilder<TApplication>::ApplicationBuilder()
    {
        mLoggerCfg = std::make_unique<ApplicationLoggerConfiguration>();
    }

    template <typename TApplication>
    IApplicationBuilder<TApplication>& ApplicationBuilder<TApplication>::configureApplicationLogger(
        const std::function<void(ApplicationLoggerConfiguration&)> cfgCallback)
    {
        cfgCallback(*mLoggerCfg);
        return *this;
    }

    template <typename TApplication>
    std::shared_ptr<TApplication> ApplicationBuilder<TApplication>::build()
    {
        ApplicationServices::LogSinks::initialize(*mLoggerCfg);

        return std::make_shared<TApplication>();
    }
}