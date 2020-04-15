#pragma once

#include "Initializer.hpp"
#include "Xenon/Config.hpp"

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
        virtual IApplicationBuilder& configureApplicationWindow(
            std::function<void(ApplicationWindowConfiguration&)> cfgCallback) = 0;
        virtual IApplicationBuilder& configureApplicationGui(
            std::function<void(ApplicationGuiConfiguration&)> cfgCallback) = 0;
        virtual std::shared_ptr<TApplication> build() = 0;
    };

    template<typename TApplication>
    class ApplicationBuilder final : public IApplicationBuilder<TApplication>
    {
    public:
        explicit ApplicationBuilder()
        {
            mApplicationConfiguration = std::make_unique<ApplicationConfiguration>();
        }

        IApplicationBuilder<TApplication>& configureApplicationLogger(
            const std::function<void(ApplicationLoggerConfiguration&)> cfgCallback) override
        {
            cfgCallback(mApplicationConfiguration->loggerConfiguration);
            return *this;
        }

        IApplicationBuilder<TApplication>& configureApplicationWindow(
            const std::function<void(ApplicationWindowConfiguration&)> cfgCallback) override
        {
            cfgCallback(mApplicationConfiguration->windowConfiguration);
            return *this;
        }

        IApplicationBuilder<TApplication>& configureApplicationGui(
            const std::function<void(ApplicationGuiConfiguration&)> cfgCallback) override
        {
            cfgCallback(mApplicationConfiguration->guiConfiguration);
            return *this;
        }

        std::shared_ptr<TApplication> build() override
        {
            Initializer::initialize(*mApplicationConfiguration);

            const auto app = std::make_shared<TApplication>(*mApplicationConfiguration);
            Initializer::registerApplication(app);

            Initializer::assertIsInitialized();
            return app;
        }

    private:
        std::unique_ptr<ApplicationConfiguration> mApplicationConfiguration;
    };
}