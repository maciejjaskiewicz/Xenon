#pragma once

#include "Initializer.hpp"
#include "../Services/Log/ApplicationLoggerConfiguration.hpp"

#include <memory>
#include <functional>

namespace Xenon
{
    template<typename TApplication>
    class IApplicationBuilder
    {
    public:
        virtual ~IApplicationBuilder() = default;

        virtual IApplicationBuilder& configureApplicationLogger(
            std::function<void(ApplicationLoggerConfiguration&)> cfgCallback) = 0;
        virtual std::shared_ptr<TApplication> build() = 0;
    };

    template<typename TApplication>
    class ApplicationBuilder final : public IApplicationBuilder<TApplication>
    {
    public:
        explicit ApplicationBuilder()
        {
            mLoggerCfg = std::make_unique<ApplicationLoggerConfiguration>();
        }

        IApplicationBuilder<TApplication>& configureApplicationLogger(
            const std::function<void(ApplicationLoggerConfiguration&)> cfgCallback) override
        {
            cfgCallback(*mLoggerCfg);
            return *this;
        }

        std::shared_ptr<TApplication> build() override
        {
            Initializer::initialize(*mLoggerCfg);

            const auto app = std::make_shared<TApplication>();
            Initializer::registerApplication(app);

            Initializer::assertIsInitialized();
            return app;
        }

    private:
        std::unique_ptr<ApplicationLoggerConfiguration> mLoggerCfg;
    };
}