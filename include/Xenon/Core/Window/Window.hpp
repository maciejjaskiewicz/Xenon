#pragma once

#include "../Api.hpp"
#include "../../Config/ApplicationWindowConfiguration.hpp"

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Xenon
{
    struct WindowData
    {
        std::string title;
        WindowResolution resolution{};
        bool vSync{ false };
        bool maximized{ false };
    };

    class Window
    {
    public:
        explicit Window(const std::string& title = "Xenon", 
                        const WindowResolution& resolution = WindowResolution(), 
                        bool vSync = false,
                        bool maximized = false);
        explicit Window(const ApplicationWindowConfiguration& windowConfiguration);
        ~Window();

        void update() const;
        void setVSync(bool enabled);

        XN_NODISCARD GLFWwindow& glfwWindow() const noexcept;
        XN_NODISCARD WindowResolution resolution() const noexcept;
        XN_NODISCARD bool vSync() const noexcept;
        XN_NODISCARD bool maximized() const noexcept;

        Window(const Window& other) = delete;
        Window(Window&& other) = delete;
        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) = delete;

    private:
        void init();
        void shutDown() const;

        GLFWwindow* mWindow{ nullptr };
        WindowData mData{};

        inline static uint8_t sGLFWWindowCount { 0 };
    };
}
