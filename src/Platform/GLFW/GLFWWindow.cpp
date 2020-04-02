#include "GLFWWindow.hpp"

#include <GLFW/glfw3.h>

namespace Xenon
{
    GLFWWindow::GLFWWindow(const WindowConfiguration& windowConfiguration)
    {
        mData.title = windowConfiguration.title;
        mData.resolution = windowConfiguration.resolution;
        mData.vSync = windowConfiguration.vSync;
        mData.maximized = windowConfiguration.maximized;
    }

    void GLFWWindow::init()
    {
        XN_ENG_INFO("Creating window: [{}]({}, {}), VSync: {}", mData.title,
            mData.resolution.width, mData.resolution.height, mData.vSync);

        if (sGLFWWindowCount == 0)
        {
            const auto initialized = glfwInit();
            XN_ASSERT_COM(initialized, "Could not intialize GLFW!");

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            glfwSetErrorCallback([](const int error, const char* description)
            {
                XN_ENG_CRITICAL("GLFW Error: [{}] {}", error, description);
            });

            XN_ENG_DEBUG("GLFW successfully initialized");
        }

        mData.maximized ? glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE) : glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);

        const auto width = static_cast<int>(mData.resolution.width);
        const auto height = static_cast<int>(mData.resolution.height);
        mWindow = glfwCreateWindow(width, height, mData.title.c_str(), nullptr, nullptr);

        glfwSetWindowUserPointer(mWindow, reinterpret_cast<void*>(&mData));

        mGraphicsContext = GraphicsContext::create(reinterpret_cast<void*>(mWindow));
        mGraphicsContext->init();

        setVSync(mData.vSync);

        sGLFWWindowCount++;
        mInitialized = true;
    }

    GLFWWindow::~GLFWWindow()
    {
        shutDown();
    }

    void GLFWWindow::update() const
    {
        XN_ASSERT_COM(mInitialized, "Window is uninitialized!");

        glfwPollEvents();
        mGraphicsContext->swapBuffers();
    }

    void GLFWWindow::setVSync(const bool enabled)
    {
        if (enabled)
        {
            XN_ENG_DEBUG("Turing on VSync for [{}] window", mData.title);
            glfwSwapInterval(1);
        }
        else
        {
            XN_ENG_DEBUG("Turing off VSync for [{}] window", mData.title);
            glfwSwapInterval(0);
        }

        mData.vSync = enabled;
    }

    void* GLFWWindow::window() const noexcept
    {
        XN_ASSERT_COM(mInitialized, "Window is uninitialized!");
        return reinterpret_cast<void*>(mWindow);
    }

    XN_NODISCARD WindowResolution GLFWWindow::resolution() const noexcept
    {
        return mData.resolution;
    }

    XN_NODISCARD bool GLFWWindow::vSync() const noexcept
    {
        return mData.vSync;
    }

    XN_NODISCARD bool GLFWWindow::maximized() const noexcept
    {
        return mData.maximized;
    }

    void GLFWWindow::shutDown() const
    {
        XN_ASSERT_COM(mInitialized, "Window is uninitialized!");

        glfwDestroyWindow(mWindow);
        sGLFWWindowCount--;

        if (sGLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }
}