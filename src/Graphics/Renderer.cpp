#include <Graphics/Renderer.hpp>

#include <Graphics/API/RendererAPI.hpp>
#include <Graphics/RenderCmd.hpp>
#include <Core/ApplicationServices.hpp>
#include <Core/Events/WindowEvent.hpp>
#include "Core/InternalApplicationServices.hpp"

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

        mAPIDetails = InternalApplicationServices::RendererAPI::ref().fetchRendererDetails();
    }

    void Renderer::beginScene(const Camera& camera)
    {
        mViewProjectionMatrix = camera.viewProjectionMatrix();
    }

    void Renderer::endScene()
    {
    }

    void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
        const glm::mat4& transform) const
    {
        shader->bind();
        shader->setMat4("uViewProjection", mViewProjectionMatrix);
        shader->setMat4("uTransform", transform);

        vertexArray->bind();
        RenderCmd::draw(vertexArray);
    }

    XN_NODISCARD const RendererAPIDetails& Renderer::getDetails() const
    {
        return mAPIDetails;
    }
}
