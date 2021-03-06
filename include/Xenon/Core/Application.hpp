#pragma once

#include "Xenon/Config/ApplicationConfiguration.hpp"
#include "ApplicationServices.hpp"
#include "Window/Window.hpp"
#include "Events/WindowEvent.hpp"
#include "Gui/Gui.hpp"
#include "Xenon/Utils/DeltaTime.hpp"

namespace Xenon
{
    class Application
    {
    public:
        virtual ~Application();

        void run();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;
        Application& operator=(Application const&) = delete;

        using Services = ApplicationServices;
    protected:
        explicit Application(const ApplicationConfiguration&);

        virtual void init();

        virtual void update(const DeltaTime& deltaTime) = 0;
        virtual void updateGui(const DeltaTime& deltaTime);
        virtual void onCloseEvent(const WindowCloseEvent&);

        std::unique_ptr<Window> mWindow;
        std::unique_ptr<Gui> mGui;
        bool mRunning{ true };

        template<typename> friend class ApplicationBuilder;
    };
}
