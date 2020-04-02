#include <Xenon/Graphics/GraphicsContext.hpp>

#include "../Platform/OpenGL/OpenGLContext.hpp"

namespace Xenon
{
    std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window)
    {
        return std::make_unique<OpenGLGraphicsContext>(window);
    }
}
