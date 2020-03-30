#pragma once

#include "Window.hpp"

namespace Xenon
{
    class WindowEventManager
    {
    public:
        explicit WindowEventManager(Window&);
        void registerEvents() const;

    private:
        static void windowCloseCallback(GLFWwindow*);
        static void windowSizeCallback(GLFWwindow*, int, int);
        static void keyCallback(GLFWwindow*, int, int, int, int);
        static void charCallback(GLFWwindow*, unsigned);
        static void mouseButtonCallback(GLFWwindow*, int, int, int);
        static void cursorPosCallback(GLFWwindow*, double, double);
        static void scrollCallback(GLFWwindow*, double, double);

        Window& mWindow;
    };
}

