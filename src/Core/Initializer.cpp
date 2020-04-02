#include <Xenon/Core/Initializer.hpp>

#include <Xenon/Core.hpp>
#include <Xenon/Services/Log/Logger.hpp>
#include <Xenon/Services/Event/EventBus.hpp>

#include "InternalApplicationServices.hpp"
#include "../Services/Log/InternalLogger.hpp"
#include "../Services/Log/ConsoleLogSink.hpp"
#include "../Services/Log/FileLogSink.hpp"
#include "Input/NullInput.hpp"

namespace Xenon
{
    void Initializer::initialize(const ApplicationConfiguration& applicationConfiguration)
    {
        XN_ASSERT_COM(!initialized, "Already initialized!")

        initializeLogging(applicationConfiguration.loggerConfiguration);
        initializeEventSystem();
        initializeInput();

        initialized = true;
        XN_ENG_INFO("Xenon initialized successfully");
    }

    void Initializer::registerApplication(const std::shared_ptr<Application>& application)
    {
        InternalApplicationServices::App::set(application);
    }

    void Initializer::assertIsInitialized()
    {
        InternalApplicationServices::assertIsInitialized();
        Application::Services::assertIsInitialized();
    }

    void Initializer::initializeLogging(const ApplicationLoggerConfiguration& logCfg)
    {
        using LogSinks = InternalApplicationServices::LogSinks;
        using XenonLogger = InternalApplicationServices::Log;

        // Init sinks
        LogSinks::Console::createAndSet<NullConsoleLogSink>();
        LogSinks::Console::createAndSet<NullConsoleLogSink>();

        const auto& consoleSinkCfg = logCfg.consoleLoggerCfg();
        if (consoleSinkCfg.enabled)
        {
            LogSinks::Console::createAndSet<ConsoleLogSink>();
        }

        const auto& fileLogCfg = logCfg.fileLoggerCfg();
        if (fileLogCfg.enabled)
        {
            LogSinks::File::createAndSet<FileLogSink>(
                fileLogCfg.fileName,
                fileLogCfg.truncate
            );
        }

        // Xenon logger
        const auto xenonLogger = std::make_shared<Logger>("Xenon");
        XenonLogger::set(xenonLogger);
        auto internalLogger = reinterpret_cast<IInternalLogger*>(xenonLogger->mImpl.get());
        spdlog::set_default_logger(internalLogger->getInternal());

        // Client logger
        const auto clientLogger = std::make_shared<Logger>(logCfg.label());
        Application::Services::Logger::set(clientLogger);

        // Global log configuration
        GlobalLogConfiguration::sAppLoggerName = clientLogger->name();
    }

    void Initializer::initializeEventSystem()
    {
        const auto eventBus = std::make_shared<EventBus>();
        Application::Services::EventBus::set(eventBus);
    }

    void Initializer::initializeInput()
    {
        const auto input = std::make_shared<NullInput>();
        Application::Services::Input::set(input);
    }
}