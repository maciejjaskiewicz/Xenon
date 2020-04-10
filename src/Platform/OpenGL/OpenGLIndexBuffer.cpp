#include "OpenGLIndexBuffer.hpp"

#include <glad/glad.h>

namespace Xenon
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, const uint32_t count)
        : mCount(count)
    {
        glGenBuffers(1, &mIndexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);

        const auto bufferSize = sizeof(uint32_t) * count;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &mIndexBufferId);
    }

    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t OpenGLIndexBuffer::count() const noexcept
    {
        return mCount;
    }
}