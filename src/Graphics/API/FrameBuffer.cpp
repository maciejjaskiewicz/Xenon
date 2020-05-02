#include <Graphics/API/FrameBuffer.hpp>

#include "Platform/OpenGL/OpenGLFrameBuffer.hpp"

namespace Xenon
{
    std::shared_ptr<FrameBuffer> FrameBuffer::create(const uint32_t width, const uint32_t height)
    {
        return std::make_shared<OpenGLFrameBuffer>(width, height);
    }
}
