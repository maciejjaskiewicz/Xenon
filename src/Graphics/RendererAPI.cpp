#include <Xenon/Graphics/RendererAPI.hpp>

#include "../Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Xenon
{
    XN_NODISCARD std::unique_ptr<RendererAPI> RendererAPI::create()
    {
        return std::make_unique<OpenGLRendererAPI>();
    }

    XN_NODISCARD std::shared_ptr<RendererAPI> RendererAPI::createShared()
    {
        return std::make_shared<OpenGLRendererAPI>();
    }
}