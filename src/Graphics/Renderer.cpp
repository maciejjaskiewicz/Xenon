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

    void Renderer::submit(const std::weak_ptr<Shader>& shader, const std::weak_ptr<VertexArray>& vertexArray) const
    {
        const auto sShader = shader.lock();
        const auto sVertexArray = vertexArray.lock();

        if(sShader && sVertexArray)
        {
            sShader->bind();
            sShader->setMat4("uViewProjection", mViewProjectionMatrix);

            sVertexArray->bind();
            RenderCmd::draw(vertexArray);
        }
    }

    XN_NODISCARD const RendererAPIDetails& Renderer::getDetails() const
    {
        return mAPIDetails;
    }
}
