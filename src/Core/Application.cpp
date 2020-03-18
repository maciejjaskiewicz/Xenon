#include <Xenon/Core/Application.hpp>

#include <iostream>

namespace Xenon
{
    Application::Application() = default;
    Application::~Application() = default;

    void Application::run()
    {
        std::cout << "Engine test" << std::endl;
    }
}
