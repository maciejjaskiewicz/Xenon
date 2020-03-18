#pragma once

#include "Api.hpp"

namespace Xenon
{
    class XN_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;
        Application& operator=(Application const&) = delete;
    };
}