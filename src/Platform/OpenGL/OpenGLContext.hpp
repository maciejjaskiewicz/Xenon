#pragma once

#include <Xenon/Graphics/GraphicsContext.hpp>

struct GLFWwindow;

namespace Xenon
{
    class OpenGLGraphicsContext final : public GraphicsContext
    {
    public:
        explicit OpenGLGraphicsContext(void* window);

        void init() override;
        void swapBuffers() override;
    private:
        GLFWwindow* mWindow;
        bool mInitialized{ false };
    };
}