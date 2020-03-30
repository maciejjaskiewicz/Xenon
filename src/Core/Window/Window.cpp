#include <Xenon/Core/Window/Window.hpp>

#include <Xenon/Core/Log.hpp>

namespace Xenon
{
    Window::Window(const std::string& title, const WindowResolution& resolution, 
        const bool vSync, const bool maximized)
    {
        mData.title = title;
        mData.resolution = resolution;
        mData.vSync = vSync;
        mData.maximized = maximized;

        init();
    }

    Window::Window(const ApplicationWindowConfiguration& windowConfiguration)
    {
        mData.title = windowConfiguration.getTitle();
        mData.resolution = windowConfiguration.getResolution();
        mData.vSync = windowConfiguration.vSync();
        mData.maximized = windowConfiguration.isMaximized();

        init();
    }

    void Window::init()
    {
        XN_ENG_INFO("Creating window: [{}]({}, {}), VSync: {}", mData.title, 
            mData.resolution.width, mData.resolution.height, mData.vSync);

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

        mData.maximized ? glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE) : glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);

        const auto width = static_cast<int>(mData.resolution.width);
        const auto height = static_cast<int>(mData.resolution.height);
        mWindow = glfwCreateWindow(width, height, mData.title.c_str(), nullptr, nullptr);

        glfwSetWindowUserPointer(mWindow, reinterpret_cast<void*>(&mData));

        // Move graphics context class
        glfwMakeContextCurrent(mWindow);
        const auto gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        XN_ASSERT_COM(gladStatus, "Failed to initialize GLAD");

        setVSync(mData.vSync);

        sGLFWWindowCount++;
    }

    Window::~Window()
    {
        shutDown();
    }

    void Window::update() const
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }

    void Window::setVSync(const bool enabled)
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

    GLFWwindow& Window::glfwWindow() const noexcept
    {
        return *mWindow;
    }

    XN_NODISCARD WindowResolution Window::resolution() const noexcept
    {
        return mData.resolution;
    }

    XN_NODISCARD bool Window::vSync() const noexcept
    {
        return mData.vSync;
    }

    XN_NODISCARD bool Window::maximized() const noexcept
    {
        return mData.maximized;
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
