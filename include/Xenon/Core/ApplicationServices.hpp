#pragma once

#include "../Utils/ServiceLocator.hpp"
#include "../Utils/ImmutableServiceLocator.hpp"

#include "../Services/Log/Logger.hpp"
#include "../Services/Event/EventBus.hpp"

namespace Xenon
{
    struct ApplicationServices
    {
        using AppLogger = ServiceLocator<Logger>;
        using EventBus = ImmutableServiceLocator<Xenon::EventBus>;

        static void assertIsInitialized()
        {
            XN_ASSERT_COM(!AppLogger::empty(), "Uninitialized");
            EventBus::assertIsNotEmpty();
        }
    };
}
