#pragma once

#include "../Core/Api.hpp"
#include "VertexArray.hpp"

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

        static std::unique_ptr<RendererAPI> create();
        static std::shared_ptr<RendererAPI> createShared();
    };
}