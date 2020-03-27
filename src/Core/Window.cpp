#include <Xenon/Core/Window.hpp>

#include <Xenon/Core/Log.hpp>

namespace Xenon
{
    Window::Window(std::string title, const WindowResolution& resolution, const bool vSync, const bool maximized)
        : mTitle(std::move(title)), mResolution(resolution), mVSync(vSync),
          mMaximized(maximized)
    {
        init();
    }

    Window::Window(const ApplicationWindowConfiguration& windowConfiguration)
        : mTitle(windowConfiguration.getTitle()), mResolution(windowConfiguration.getResolution()),
          mVSync(windowConfiguration.vSync()), mMaximized(windowConfiguration.isMaximized())
    {
        init();
    }

    void Window::init()
    {
        XN_ENG_INFO("Creating window: [{}]({}, {}), VSync: {}", mTitle, mResolution.width, mResolution.height, mVSync);

        if(sGLFWWindowCount == 0)
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

        mMaximized ? glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE) : glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);

        const auto width = static_cast<int>(mResolution.width);
        const auto height = static_cast<int>(mResolution.height);
        mWindow = glfwCreateWindow(width, height, mTitle.c_str(), nullptr, nullptr);

        // Move graphics context class
        glfwMakeContextCurrent(mWindow);
        const auto gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        XN_ASSERT_COM(gladStatus, "Failed to initialize GLAD");

        setVSync(mVSync);

        sGLFWWindowCount++;
    }

    Window::~Window()
    {
        shutDown();
    }

    void Window::onUpdate() const
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }

    void Window::setVSync(const bool enabled)
    {
        if (enabled)
        {
            XN_ENG_DEBUG("Turing on VSync for [{}] window", mTitle);
            glfwSwapInterval(1);
        }
        else
        {
            XN_ENG_DEBUG("Turing off VSync for [{}] window", mTitle);
            glfwSwapInterval(0);
        }

        mVSync = enabled;
    }

    XN_NODISCARD WindowResolution Window::resolution() const
    {
        return mResolution;
    }

    XN_NODISCARD bool Window::vSync() const
    {
        return mVSync;
    }

    XN_NODISCARD bool Window::maximized() const
    {
        return mMaximized;
    }

    void Window::shutDown() const
    {
        glfwDestroyWindow(mWindow);
        sGLFWWindowCount--;

        if (sGLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }
}
