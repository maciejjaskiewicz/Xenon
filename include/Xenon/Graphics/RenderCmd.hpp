#pragma once

#include "VertexArray.hpp"
#include <glm/glm.hpp>

namespace Xenon
{
    class RenderCmd
    {
    public:
        static void setClearColor(const glm::vec4& color);
        static void clear();
        static void draw(const std::weak_ptr<VertexArray>& vertexArray);
    };
}