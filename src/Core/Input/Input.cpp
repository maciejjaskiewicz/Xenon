#include <Core/Input/Input.hpp>

#include "Platform/GLFW/GLFWInput.hpp"

namespace Xenon
{
    XN_NODISCARD std::unique_ptr<Input> Input::create(Window& window)
    {
        return std::make_unique<GLFWInput>(window);
    }
}
