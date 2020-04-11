#include <Xenon/Core/Application.hpp>

#include <Xenon/Core/Window/WindowEventManager.hpp>
#include <Xenon/Core/Input/Input.hpp>
#include <Xenon/Graphics/Renderer.hpp>
#include <Xenon/Services/Time/Timer.hpp>

namespace Xenon
{
    Application::Application(const ApplicationConfiguration& config)
    {
        Services::Timer::createAndSet<Timer>();

        mWindow = Window::create(WindowConfiguration(config.windowConfiguration));
        mWindow->init();

        const auto windowEventManager = WindowEventManager::create(*mWindow);
        windowEventManager->registerEvents();

        const std::shared_ptr<Input> input = Input::create(*mWindow);
        Services::Input::set(input);

        Services::Renderer::ref().init();

        mGui = Gui::create(*mWindow, GuiConfiguration(config.guiConfiguration));
        mGui->init();

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
        DeltaTime deltaTime(Services::Timer::ref().elapsed());

        while (mRunning)
        {
            deltaTime.update(Services::Timer::ref().elapsed());
            Services::EventBus::ref().update();

            if(!mWindow->minimized())
            {
                this->update(deltaTime);
            }

            mGui->newFrame();
            updateGui();
            mGui->render();

            mWindow->update();
        }
    }

    void Application::updateGui()
    { }
}