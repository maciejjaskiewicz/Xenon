#pragma once

#include "../Config/ApplicationWindowConfiguration.hpp"
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Xenon
{
    class Window
    {
    public:
        explicit Window(std::string title = "Xenon", 
                        const WindowResolution& resolution = WindowResolution(), 
                        bool vSync = false,
                        bool maximized = false);
        explicit Window(const ApplicationWindowConfiguration& windowConfiguration);
        ~Window();

        void onUpdate() const;
        void setVSync(bool enabled);

        [[nodiscard]] WindowResolution resolution() const;
        [[nodiscard]] bool vSync() const;
        [[nodiscard]] bool maximized() const;

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
        bool mVSync{ false };
        bool mMaximized{ false };

        inline static uint8_t sGLFWWindowCount { 0 };
    };
}
