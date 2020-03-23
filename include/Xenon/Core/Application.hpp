#pragma once

#include "Api.hpp"
#include "Assert.hpp"
#include "../Utils/ServiceLocator.hpp"
#include "../Services/Log/Logger.hpp"

namespace Xenon
{
    class XN_API Application
    {
    public:
        virtual ~Application();

        void run();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;
        Application& operator=(Application const&) = delete;

        static Logger& logger()
        {
            return Services::ClientLogger::ref();
        }

    protected:
        explicit Application();

    private:
        struct Services
        {
            using ClientLogger = ServiceLocator<Logger>;

            static void assertIsInitialized()
            {
                XN_ASSERT_COM(!ClientLogger::empty(), "Uninitialized");
            }
        };

        friend struct Initializer;
        template<typename> friend class ApplicationBuilder;
    };
}
