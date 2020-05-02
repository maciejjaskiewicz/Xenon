#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Xenon
{
    OpenGLRendererAPI::OpenGLRendererAPI() = default;

    void OpenGLRendererAPI::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::draw(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->indexBuffer().count(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::setViewport(const uint32_t x, const uint32_t y, 
        const uint32_t width, const uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    RendererAPIDetails OpenGLRendererAPI::fetchRendererDetails()
    {
        return RendererAPIDetails
        {
            "OpenGL",
            fmt::format("{}", glGetString(GL_VERSION)),
            fmt::format("{}", glGetString(GL_VENDOR)),
            fmt::format("{}", glGetString(GL_RENDERER)),
        };
    }
}
