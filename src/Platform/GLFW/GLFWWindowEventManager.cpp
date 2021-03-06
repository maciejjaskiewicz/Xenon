#include "GLFWWindowEventManager.hpp"

#include <Core/ApplicationServices.hpp>
#include <Core/Events/WindowEvent.hpp>
#include <Core/Events/KeyEvent.hpp>
#include <Core/Events/MouseEvent.hpp>

#include <GLFW/glfw3.h>

namespace Xenon
{
    GLFWWindowEventManager::GLFWWindowEventManager(Window& window)
        : mWindow(reinterpret_cast<GLFWwindow*>(window.window()))
    { }

    void GLFWWindowEventManager::registerEvents() const
    {
        glfwSetWindowCloseCallback(mWindow, windowCloseCallback);
        glfwSetWindowSizeCallback(mWindow, windowSizeCallback);
        glfwSetWindowMaximizeCallback(mWindow, windowMaximizeCallback);
        glfwSetKeyCallback(mWindow, keyCallback);
        glfwSetCharCallback(mWindow, charCallback);
        glfwSetMouseButtonCallback(mWindow, mouseButtonCallback);
        glfwSetCursorPosCallback(mWindow, cursorPosCallback);
        glfwSetScrollCallback(mWindow, scrollCallback);
    }

    void GLFWWindowEventManager::windowCloseCallback(GLFWwindow* window)
    {
        ApplicationServices::EventBus::ref().enqueue<WindowCloseEvent>();
    }

    void GLFWWindowEventManager::windowSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        auto* windowData = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

        windowData->resolution.width = static_cast<uint32_t>(width);
        windowData->resolution.height = static_cast<uint32_t>(height);
        windowData->minimized = (width == 0 || height == 0);

        ApplicationServices::EventBus::ref().trigger<WindowResizeEvent>(windowData->resolution);
    }

    void GLFWWindowEventManager::windowMaximizeCallback(GLFWwindow* window, const int maximized)
    {
        auto* windowData = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

        windowData->maximized = (maximized == GLFW_TRUE);
    }

    void GLFWWindowEventManager::keyCallback(GLFWwindow* window, const int key, const int scanCode, const int action, const int mods)
    {
        const auto keyCode = static_cast<KeyCode>(key);

        switch (action)
        {
        case GLFW_PRESS:
            ApplicationServices::EventBus::ref().trigger<KeyPressedEvent>(keyCode, false);
            break;
        case GLFW_REPEAT:
            ApplicationServices::EventBus::ref().trigger<KeyPressedEvent>(keyCode, true);
            break;
        case GLFW_RELEASE:
            ApplicationServices::EventBus::ref().trigger<KeyReleasedEvent>(keyCode);
            break;
        default: return;
        }
    }

    void GLFWWindowEventManager::charCallback(GLFWwindow* window, const unsigned keyCode)
    {
        ApplicationServices::EventBus::ref().trigger<KeyTypedEvent>(static_cast<KeyCode>(keyCode));
    }

    void GLFWWindowEventManager::mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods)
    {
        const auto mouseButtonCode = static_cast<MouseButtonCode>(button);

        switch (action)
        {
        case GLFW_PRESS:
            ApplicationServices::EventBus::ref().trigger<MouseButtonPressedEvent>(mouseButtonCode);
            break;
        case GLFW_RELEASE:
            ApplicationServices::EventBus::ref().trigger<MouseButtonReleasedEvent>(mouseButtonCode);
            break;
        default: return;
        }
    }

    void GLFWWindowEventManager::cursorPosCallback(GLFWwindow* window, const double xOffset, const double yOffset)
    {
        const auto xOffsetF = static_cast<float>(xOffset);
        const auto yOffsetF = static_cast<float>(yOffset);

        ApplicationServices::EventBus::ref().trigger<MouseMovedEvent>(xOffsetF, yOffsetF);
    }

    void GLFWWindowEventManager::scrollCallback(GLFWwindow* window, const double xOffset, const double yOffset)
    {
        const auto xOffsetF = static_cast<float>(xOffset);
        const auto yOffsetF = static_cast<float>(yOffset);

        ApplicationServices::EventBus::ref().trigger<MouseScrolledEvent>(xOffsetF, yOffsetF);
    }
}
