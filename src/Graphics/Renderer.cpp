#include <Xenon/Graphics/Renderer.hpp>
#include <Xenon/Graphics/RendererAPI.hpp>
#include <Xenon/Graphics/RenderCmd.hpp>
#include <Xenon/Core/ApplicationServices.hpp>
#include <Xenon/Core/Events/WindowEvent.hpp>

#include "../Core/InternalApplicationServices.hpp"

namespace Xenon
{
    Renderer::Renderer() = default;

    void Renderer::init()
    {
        InternalApplicationServices::RendererAPI::ref().init();

        ApplicationServices::EventBus::ref().subscribe<WindowResizeEvent>(
            [](const WindowResizeEvent& event)
        {
            RenderCmd::setViewport(0, 0, event.resolution.width, event.resolution.height);
        });
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
