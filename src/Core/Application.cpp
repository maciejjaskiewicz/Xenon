#include <Xenon/Core/Log.hpp>
#include <Xenon/Core/Application.hpp>
#include "InternalApplicationServices.hpp"

namespace Xenon
{
    Application::Application() = default;

    Application::~Application() = default;

    void Application::run()
    {
        XN_INTERNAL_INFO("{} Engine test", "Xenon");
    }
}
