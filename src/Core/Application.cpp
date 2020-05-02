#include <Core/Application.hpp>

#include <Core/Window/WindowEventManager.hpp>
#include <Core/Input/Input.hpp>
#include <Graphics/Renderer.hpp>
#include <Services/Time/Timer.hpp>

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
        init();

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
            updateGui(deltaTime);
            mGui->render();

            mWindow->update();
        }
    }

    void Application::init()
    { }

    void Application::updateGui(const DeltaTime& deltaTime)
    { }
}