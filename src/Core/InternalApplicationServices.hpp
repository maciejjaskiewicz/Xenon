#pragma once

#include <Xenon/Utils/ServiceLocator.hpp>
#include <Xenon/Utils/ImmutableServiceLocator.hpp>

#include "../Services/Log/LogSink.hpp"

namespace Xenon
{
    class Application;
    class Logger;

    struct InternalApplicationServices
    {
        using App = ImmutableServiceLocator<Application>;
        using Log = ImmutableServiceLocator<Logger>;

        struct LogSinks
        {
            using Console = ServiceLocator<IConsoleLogSink>;
            using File = ServiceLocator<IFileLogSink>;
        };

        static void assertIsInitialized()
        {
            App::assertIsNotEmpty();
            Log::assertIsNotEmpty();

            XN_ASSERT_COM(!LogSinks::Console::empty(), "Uninitialized");
            XN_ASSERT_COM(!LogSinks::File::empty(), "Uninitialized");
        }
    };
}