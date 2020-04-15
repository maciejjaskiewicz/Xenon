#include <Core/Window/Window.hpp>

#include "Platform/GLFW/GLFWWindow.hpp"

namespace Xenon
{
    XN_NODISCARD std::unique_ptr<Window> Window::create(const WindowConfiguration& windowConfiguration)
    {
        return std::make_unique<GLFWWindow>(windowConfiguration);
    }
}