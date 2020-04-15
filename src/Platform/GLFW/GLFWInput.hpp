#pragma once

#include <Core/Input/Input.hpp>

#include <GLFW/glfw3.h>

namespace Xenon
{
    class GLFWInput final : public Input
    {
    public:
        explicit GLFWInput(Window& window);

        XN_NODISCARD bool isKeyPressed(KeyCode key) const override;
        XN_NODISCARD bool isMouseButtonPressed(MouseButtonCode mouseButton) const override;

        XN_NODISCARD std::pair<float, float> mousePosition() const override;

    private:
        GLFWwindow* mWindow;
        bool mInitialized{ false };
    };
}
