#include <Xenon/Graphics/IndexBuffer.hpp>

#include "../Platform/OpenGL/OpenGLIndexBuffer.hpp"

namespace Xenon
{
    XN_NODISCARD std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t* indices, const uint32_t count)
    {
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
    }
}