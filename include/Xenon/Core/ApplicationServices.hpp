#pragma once

#include "Xenon/Utils/ServiceLocator.hpp"
#include "Xenon/Utils/ImmutableServiceLocator.hpp"

#include "Xenon/Services/Event/EventBus.hpp"

namespace Xenon
{
    class Timer;
    class Logger;
    class Input;
    class Renderer;

    struct ApplicationServices
    {
        using Timer = ServiceLocator<Xenon::Timer>;
        using Logger = ServiceLocator<Xenon::Logger>;
        using EventBus = ImmutableServiceLocator<Xenon::EventBus>;
        using Input = ServiceLocator<Xenon::Input>;
        using Renderer = ServiceLocator<Xenon::Renderer>;

        static void assertIsInitialized()
        {
            XN_ASSERT_COM(!Timer::empty(), "Uninitialized");
            XN_ASSERT_COM(!Logger::empty(), "Uninitialized");
            EventBus::assertIsNotEmpty();
            XN_ASSERT_COM(!Input::empty(), "Uninitialized");
            XN_ASSERT_COM(!Renderer::empty(), "Uninitialized");
        }
    };
}