#include <Xenon/Core/Application.hpp>

#include <Xenon/Core/Window/WindowEventManager.hpp>

namespace Xenon
{
    Application::Application(const ApplicationConfiguration& config)
    {
        mWindow = std::make_unique<Window>(config.windowConfiguration);

        const WindowEventManager windowEventManager(*mWindow);
        windowEventManager.registerEvents();

        Services::EventBus::ref().subscribe<WindowCloseEvent, &Application::onCloseEvent>(this);
    }

    void Application::onCloseEvent(const WindowCloseEvent& event)
    {
        XN_ENG_INFO("Closing application");

        mRunning = false;
    }

    Application::~Application() = default;

    void Application::run() const
    {
        while (mRunning)
        {
            Services::EventBus::ref().update();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            mWindow->update();
        }
    }
}
