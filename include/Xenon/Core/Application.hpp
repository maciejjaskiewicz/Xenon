#pragma once

#include "../Config/ApplicationConfiguration.hpp"
#include "ApplicationServices.hpp"
#include "Window/Window.hpp"
#include "Events/WindowEvent.hpp"

namespace Xenon
{
    class Application
    {
    public:
        virtual ~Application();

        void run() const;

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;
        Application& operator=(Application const&) = delete;

        using Services = ApplicationServices;
    protected:
        explicit Application(const ApplicationConfiguration&);

        virtual void onCloseEvent(const WindowCloseEvent&);

        std::unique_ptr<Window> mWindow;
        bool mRunning{ true };

        template<typename> friend class ApplicationBuilder;
    };
}
