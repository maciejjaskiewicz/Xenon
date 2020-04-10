#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Xenon
{
    OpenGLRendererAPI::OpenGLRendererAPI() = default;

    void OpenGLRendererAPI::init()
    {
        //...
    }

    void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::draw(const std::weak_ptr<VertexArray> vertexArray)
    {
        XN_ASSERT(!vertexArray.expired());

        if(const auto sVertexArray = vertexArray.lock())
        {
            glDrawElements(GL_TRIANGLES, sVertexArray->indexBuffer().count(), GL_UNSIGNED_INT, nullptr);
        }
    }
}