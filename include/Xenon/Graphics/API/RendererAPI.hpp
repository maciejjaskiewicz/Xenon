#pragma once

#include "VertexArray.hpp"
#include "RendererAPIDetails.hpp"

#include <glm/glm.hpp>

namespace Xenon
{
    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual void init() = 0;

        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() const = 0;
        virtual void draw(std::weak_ptr<VertexArray> vertexArray) = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        XN_NODISCARD virtual RendererAPIDetails fetchRendererDetails() = 0;

        static std::unique_ptr<RendererAPI> create();
        static std::shared_ptr<RendererAPI> createShared();
    };
}