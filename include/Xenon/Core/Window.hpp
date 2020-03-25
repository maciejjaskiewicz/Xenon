#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Xenon
{
    struct WindowResolution
    {
        explicit WindowResolution(const uint32_t windowWidth = 1280, 
            const uint32_t windowHeight = 720) : width(windowWidth), height(windowHeight)
        { }

        uint32_t width;
        uint32_t height;
    };

    class Window
    {
    public:
        explicit Window(std::string title = "Xenon", 
                        const WindowResolution& resolution = WindowResolution(), 
                        bool vSync = false);
        ~Window();

        void onUpdate() const;
        void setVSync(bool enabled);

        [[nodiscard]] WindowResolution resolution() const;
        [[nodiscard]] bool vSync() const;

        Window(const Window& other) = delete;
        Window(Window&& other) = delete;
        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) = delete;

    private:
        void init();
        void shutDown() const;

        GLFWwindow* mWindow{ nullptr };

        std::string mTitle;
        WindowResolution mResolution;
        bool mVSync { false };

        inline static uint8_t sGLFWWindowCount { 0 };
    };
}
