#pragma once

#include <Xenon/Core/Window/WindowEventManager.hpp>

#include "GLFWWindow.hpp"

namespace Xenon
{
    class GLFWWindowEventManager final : public WindowEventManager
    {
    public:
        explicit GLFWWindowEventManager(Window& window);
        void registerEvents() const override;

    private:
        static void windowCloseCallback(GLFWwindow*);
        static void windowSizeCallback(GLFWwindow*, int, int);
        static void windowMaximizeCallback(GLFWwindow*, int);
        static void keyCallback(GLFWwindow*, int, int, int, int);
        static void charCallback(GLFWwindow*, unsigned);
        static void mouseButtonCallback(GLFWwindow*, int, int, int);
        static void cursorPosCallback(GLFWwindow*, double, double);
        static void scrollCallback(GLFWwindow*, double, double);

        GLFWwindow* mWindow;
    };
}