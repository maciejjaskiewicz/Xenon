#include <Xenon/Core/Log.hpp>
#include <Xenon/Core/Application.hpp>
#include "InternalApplicationServices.hpp"

namespace Xenon
{
    Application::Application() = default;

    Application::~Application() = default;

    void Application::run()
    {
        XN_ENG_INFO("{} Engine test", "Xenon");
    }

    void Application::Services::assertIsInitialized()
    {
        XN_ASSERT_COM(!AppLogger::empty(), "Uninitialized");
    }
}
