#include <Xenon/Graphics/RenderCmd.hpp>
#include <Xenon/Graphics/RendererAPI.hpp>

#include "../Core/InternalApplicationServices.hpp"

namespace Xenon
{
    void RenderCmd::setClearColor(const glm::vec4& color)
    {
        InternalApplicationServices::RendererAPI::ref().setClearColor(color);
    }

    void RenderCmd::clear()
    {
        InternalApplicationServices::RendererAPI::ref().clear();
    }

    void RenderCmd::draw(const std::weak_ptr<VertexArray>& vertexArray)
    {
        InternalApplicationServices::RendererAPI::ref().draw(vertexArray);
    }

    void RenderCmd::setViewport(const uint32_t x, const uint32_t y, 
        const uint32_t width, const uint32_t height)
    {
        InternalApplicationServices::RendererAPI::ref().setViewport(x, y, width, height);
    }
}
