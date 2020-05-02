#pragma once

#include <Graphics/API/RendererAPI.hpp>

namespace Xenon
{
    class OpenGLRendererAPI final : public RendererAPI
    {
    public:
        explicit OpenGLRendererAPI();

        void init() override;

        void setClearColor(const glm::vec4& color) override;
        void clear() const override;
        void draw(const std::shared_ptr<VertexArray>& vertexArray) override;
        void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        XN_NODISCARD RendererAPIDetails fetchRendererDetails() override;
    };
}