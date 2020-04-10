#include "OpenGLVertexBuffer.hpp"

#include <glad/glad.h>

namespace Xenon
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, const uint32_t size)
    {
        glGenBuffers(1, &mVertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &mVertexBufferId);
    }

    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
    {
        mLayout = layout;
    }

    XN_NODISCARD const BufferLayout& OpenGLVertexBuffer::layout() const
    {
        return mLayout;
    }
}