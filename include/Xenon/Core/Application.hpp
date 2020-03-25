#pragma once

#include "../Utils/ServiceLocator.hpp"
#include "../Services/Log/Logger.hpp"
#include "Window.hpp"

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

        struct Services
        {
            using AppLogger = ServiceLocator<Logger>;

            static void assertIsInitialized();
        };

    protected:
        explicit Application();

    private:
        std::unique_ptr<Window> mWindow;
        bool mRunning{ true };

        template<typename> friend class ApplicationBuilder;
    };
}
