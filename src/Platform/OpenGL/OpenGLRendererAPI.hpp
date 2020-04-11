#pragma once

#include <Xenon/Graphics/RendererAPI.hpp>

namespace Xenon
{
    class OpenGLRendererAPI final : public RendererAPI
    {
    public:
        explicit OpenGLRendererAPI();

        void init() override;

        void setClearColor(const glm::vec4& color) override;
        void clear() const override;
        void draw(std::weak_ptr<VertexArray> vertexArray) override;
        void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };
}