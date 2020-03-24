#pragma once

#include "../Utils/ServiceLocator.hpp"
#include "../Services/Log/Logger.hpp"

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

        struct Services
        {
            using AppLogger = ServiceLocator<Logger>;

            static void assertIsInitialized();
        };

    protected:
        explicit Application();

    private:
        template<typename> friend class ApplicationBuilder;
    };
}
