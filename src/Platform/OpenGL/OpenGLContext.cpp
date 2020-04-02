#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Xenon
{
    OpenGLGraphicsContext::OpenGLGraphicsContext(void* window)
        : mWindow(reinterpret_cast<GLFWwindow*>(window))
    { }

    void OpenGLGraphicsContext::init()
    {
        glfwMakeContextCurrent(mWindow);

        const auto gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        XN_ASSERT_COM(gladStatus, "Failed to initialize GLAD");

        XN_INFO("OpenGL context created");
        XN_INFO("Vendor: {}", glGetString(GL_VENDOR));
        XN_INFO("Version: {}", glGetString(GL_VERSION));
        XN_INFO("Renderer: {}", glGetString(GL_RENDERER));

        mInitialized = true;
    }

    void OpenGLGraphicsContext::swapBuffers()
    {
        XN_ASSERT_COM(mInitialized, "Graphics context is uninitialized!");
        glfwSwapBuffers(mWindow);
    }
}
