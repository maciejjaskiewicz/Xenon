#include <Xenon/Core/Application.hpp>
#include <Xenon/Core/Assert.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Xenon
{
    Application::Application() = default;
    Application::~Application() = default;

    void Application::run()
    {
        XN_ASSERT_COM(false, "Test assert");

        spdlog::set_pattern("[%T.%e][%n]%^[%l]%$ %v");
        auto logger = spdlog::stdout_color_mt("Xenon");

        logger->info("{} Engine test", "Xenon");
    }
}
