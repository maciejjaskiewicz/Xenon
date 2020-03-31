#pragma once

#include <Xenon/Core/Api.hpp>
#include <Xenon/Core/Window/Window.hpp>
#include <Xenon/Core/Window/WindowResolution.hpp>
#include <Xenon/Config/ApplicationWindowConfiguration.hpp>

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

    class CommonWindow final : public Window
    {
    public:
        explicit CommonWindow(const std::string& title = "Xenon", 
                              const WindowResolution& resolution = WindowResolution(), 
                              bool vSync = false, 
                              bool maximized = false);
        explicit CommonWindow(const ApplicationWindowConfiguration& windowConfiguration);
        ~CommonWindow();

        void update() const override;
        void setVSync(bool enabled) override;

        XN_NODISCARD void* window() const noexcept override;
        XN_NODISCARD WindowResolution resolution() const noexcept override;
        XN_NODISCARD bool vSync() const noexcept override;
        XN_NODISCARD bool maximized() const noexcept override;

        CommonWindow(const CommonWindow& other) = delete;
        CommonWindow(CommonWindow&& other) = delete;
        CommonWindow& operator=(const CommonWindow& other) = delete;
        CommonWindow& operator=(CommonWindow&& other) = delete;

    private:
        void init();
        void shutDown() const;

        GLFWwindow* mWindow{ nullptr };
        WindowData mData{};

        inline static uint8_t sGLFWWindowCount{ 0 };
    };
}
