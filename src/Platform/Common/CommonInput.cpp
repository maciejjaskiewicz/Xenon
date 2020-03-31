#include "CommonInput.hpp"

namespace Xenon
{
    CommonInput::CommonInput(Window& window)
        : mWindow(reinterpret_cast<GLFWwindow*>(window.window()))
    { }

    XN_NODISCARD bool CommonInput::isKeyPressed(KeyCode key) const
    {
        const auto state = glfwGetKey(mWindow, static_cast<int>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    XN_NODISCARD bool CommonInput::isMouseButtonPressed(MouseButtonCode mouseButton) const
    {
        const auto state = glfwGetMouseButton(mWindow, static_cast<int>(mouseButton));
        return state == GLFW_PRESS;
    }

    XN_NODISCARD std::pair<float, float> CommonInput::mousePosition() const
    {
        double x, y;
        glfwGetCursorPos(mWindow, &x, &y);

        return std::make_pair(static_cast<float>(x), static_cast<float>(y));
    }
}
