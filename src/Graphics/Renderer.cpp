#include <Xenon/Graphics/Renderer.hpp>
#include <Xenon/Graphics/RendererAPI.hpp>
#include <Xenon/Graphics/RenderCmd.hpp>

#include "../Core/InternalApplicationServices.hpp"

namespace Xenon
{
    Renderer::Renderer() = default;

    void Renderer::init()
    {
        InternalApplicationServices::RendererAPI::ref().init();
    }

    void Renderer::beginScene()
    {

    }

    void Renderer::endScene()
    {
    }

    void Renderer::submit(const std::weak_ptr<VertexArray>& vertexArray)
    {
        vertexArray.lock()->bind();
        RenderCmd::draw(vertexArray);
    }
}
