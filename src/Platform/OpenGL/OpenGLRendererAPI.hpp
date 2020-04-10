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
    };
}