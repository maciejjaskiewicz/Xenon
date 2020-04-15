#include <Graphics/API/VertexBuffer.hpp>

#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

namespace Xenon
{
    XN_NODISCARD std::shared_ptr<VertexBuffer> VertexBuffer::create(float* vertices, const uint32_t size)
    {
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }
}