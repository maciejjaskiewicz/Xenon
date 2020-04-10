#pragma once

#include <Xenon/Utils/ServiceLocator.hpp>
#include <Xenon/Utils/ImmutableServiceLocator.hpp>

#include "../Services/Log/LogSink.hpp"

namespace Xenon
{
    class Application;
    class Logger;
    class RendererAPI;

    struct InternalApplicationServices
    {
        using Application = ImmutableServiceLocator<Xenon::Application>;
        using Logger = ImmutableServiceLocator<Xenon::Logger>;
        using RendererAPI = ImmutableServiceLocator<Xenon::RendererAPI>;

        struct LogSinks
        {
            using Console = ServiceLocator<IConsoleLogSink>;
            using File = ServiceLocator<IFileLogSink>;
        };

        static void assertIsInitialized()
        {
            Application::assertIsNotEmpty();
            Logger::assertIsNotEmpty();
            RendererAPI::assertIsNotEmpty();

            XN_ASSERT_COM(!LogSinks::Console::empty(), "Uninitialized");
            XN_ASSERT_COM(!LogSinks::File::empty(), "Uninitialized");
        }
    };
}