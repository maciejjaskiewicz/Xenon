#include <Xenon/Core/Log.hpp>
#include <Xenon/Core/Application.hpp>
#include "InternalApplicationServices.hpp"

namespace Xenon
{
    Application::Application(const ApplicationConfiguration& config)
    {
        mWindow = std::make_unique<Window>(config.windowConfiguration);
    }

    Application::~Application() = default;

    void Application::run() const
    {
        while (mRunning)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            mWindow->onUpdate();
        }
    }

    void Application::Services::assertIsInitialized()
    {
        XN_ASSERT_COM(!AppLogger::empty(), "Uninitialized");
    }
}
