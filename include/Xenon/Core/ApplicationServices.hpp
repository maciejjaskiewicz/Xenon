#pragma once

#include "../Utils/ServiceLocator.hpp"
#include "../Utils/ImmutableServiceLocator.hpp"

#include "../Services/Log/Logger.hpp"
#include "../Services/Event/EventBus.hpp"
#include "Input/Input.hpp"

namespace Xenon
{
    struct ApplicationServices
    {
        using Logger = ServiceLocator<Xenon::Logger>;
        using EventBus = ImmutableServiceLocator<Xenon::EventBus>;
        using Input = ServiceLocator<Xenon::Input>;

        static void assertIsInitialized()
        {
            XN_ASSERT_COM(!Logger::empty(), "Uninitialized");
            EventBus::assertIsNotEmpty();
            XN_ASSERT_COM(!Input::empty(), "Uninitialized");
        }
    };
}
