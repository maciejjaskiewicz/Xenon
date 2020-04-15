#pragma once

#include <Core/Api.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Window/WindowResolution.hpp>
#include "Platform/OpenGL/OpenGLContext.hpp"

#include <string>

struct GLFWwindow;

namespace Xenon
{
    struct WindowData
    {
        std::string title;
        WindowResolution resolution{};
        bool vSync{ false };
        bool maximized{ false };
        bool minimized{ false };
    };

    class GLFWWindow final : public Window
    {
    public:
        explicit GLFWWindow(const WindowConfiguration& windowConfiguration);
        ~GLFWWindow();

        void init() override;
        void update() const override;
        void setVSync(bool enabled) override;

        XN_NODISCARD void* window() const noexcept override;
        XN_NODISCARD WindowResolution resolution() const noexcept override;
        XN_NODISCARD bool vSync() const noexcept override;
        XN_NODISCARD bool maximized() const noexcept override;
        XN_NODISCARD bool minimized() const noexcept override;

    private:
        void shutDown() const;

        GLFWwindow* mWindow{ nullptr };
        WindowData mData{};
        std::unique_ptr<GraphicsContext> mGraphicsContext;
        bool mInitialized{ false };

        inline static uint8_t sGLFWWindowCount{ 0 };
    };
}
