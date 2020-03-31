#pragma once

#include "Window.hpp"

namespace Xenon
{
    class WindowEventManager
    {
    public:
        virtual ~WindowEventManager() = default;
        virtual void registerEvents() const = 0;

        XN_NODISCARD static std::unique_ptr<WindowEventManager> create(Window& window);
    };
}