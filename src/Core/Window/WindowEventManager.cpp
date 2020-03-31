#include <Xenon/Core/Window/WindowEventManager.hpp>

#include <Xenon/Core/ApplicationServices.hpp>
#include <Xenon/Core/Events/WindowEvent.hpp>
#include <Xenon/Core/Events/KeyEvent.hpp>
#include <Xenon/Core/Events/MouseEvent.hpp>

#include <GLFW/glfw3.h>

namespace Xenon
{
    WindowEventManager::WindowEventManager(Window& window)
        : mWindow(window)
    { }

    void WindowEventManager::registerEvents() const
    {
        auto& glfwWindow = mWindow.glfwWindow();

        glfwSetWindowCloseCallback(&glfwWindow, windowCloseCallback);
        glfwSetWindowSizeCallback(&glfwWindow, windowSizeCallback);
        glfwSetKeyCallback(&glfwWindow, keyCallback);
        glfwSetCharCallback(&glfwWindow, charCallback);
        glfwSetMouseButtonCallback(&glfwWindow, mouseButtonCallback);
        glfwSetCursorPosCallback(&glfwWindow, cursorPosCallback);
        glfwSetScrollCallback(&glfwWindow, scrollCallback);
    }

    void WindowEventManager::windowCloseCallback(GLFWwindow* window)
    {
        ApplicationServices::EventBus::ref().enqueue<WindowCloseEvent>();
    }

    void WindowEventManager::windowSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        auto* windowData = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

        windowData->resolution.width = width;
        windowData->resolution.height = height;

        ApplicationServices::EventBus::ref().trigger<WindowResizeEvent>(windowData->resolution);
    }

    void WindowEventManager::keyCallback(GLFWwindow* window, const int key, const int scanCode, const int action, const int mods)
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

    void WindowEventManager::charCallback(GLFWwindow* window, const unsigned keyCode)
    {
        ApplicationServices::EventBus::ref().trigger<KeyTypedEvent>(static_cast<KeyCode>(keyCode));
    }

    void WindowEventManager::mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods)
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

    void WindowEventManager::cursorPosCallback(GLFWwindow* window, const double xOffset, const double yOffset)
    {
        const auto xOffsetF = static_cast<float>(xOffset);
        const auto yOffsetF = static_cast<float>(yOffset);

        ApplicationServices::EventBus::ref().trigger<MouseMovedEvent>(xOffsetF, yOffsetF);
    }

    void WindowEventManager::scrollCallback(GLFWwindow* window, const double xOffset, const double yOffset)
    {
        const auto xOffsetF = static_cast<float>(xOffset);
        const auto yOffsetF = static_cast<float>(yOffset);

        ApplicationServices::EventBus::ref().trigger<MouseScrolledEvent>(xOffsetF, yOffsetF);
    }
}
