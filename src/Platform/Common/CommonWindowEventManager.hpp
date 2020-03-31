#pragma once

#include <Xenon/Core/Window/WindowEventManager.hpp>

#include "CommonWindow.hpp"

namespace Xenon
{
    class CommonWindowEventManager final : public WindowEventManager
    {
    public:
        explicit CommonWindowEventManager(Window& window);
        void registerEvents() const override;

    private:
        static void windowCloseCallback(GLFWwindow*);
        static void windowSizeCallback(GLFWwindow*, int, int);
        static void keyCallback(GLFWwindow*, int, int, int, int);
        static void charCallback(GLFWwindow*, unsigned);
        static void mouseButtonCallback(GLFWwindow*, int, int, int);
        static void cursorPosCallback(GLFWwindow*, double, double);
        static void scrollCallback(GLFWwindow*, double, double);

        GLFWwindow* mWindow;
    };
}