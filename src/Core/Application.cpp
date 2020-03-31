#include <Xenon/Core/Application.hpp>

#include <Xenon/Core/Window/WindowEventManager.hpp>
#include <Xenon/Core/Input/Input.hpp>

namespace Xenon
{
    Application::Application(const ApplicationConfiguration& config)
    {
        mWindow = Window::create(config.windowConfiguration);

        const auto windowEventManager = WindowEventManager::create(*mWindow);
        windowEventManager->registerEvents();

        const std::shared_ptr<Input> input = Input::create(*mWindow);
        Services::Input::set(input);

        Services::EventBus::ref().subscribe<WindowCloseEvent, &Application::onCloseEvent>(this);
    }

    void Application::onCloseEvent(const WindowCloseEvent& event)
    {
        XN_ENG_INFO("Closing application");

        mRunning = false;
    }

    Application::~Application() = default;

    void Application::run()
    {
        while (mRunning)
        {
            Services::EventBus::ref().update();

            /*glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);*/
            update();

            mWindow->update();
        }
    }
}
