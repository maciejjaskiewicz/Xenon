#pragma once

#include "VertexArray.hpp"

namespace Xenon
{
    class Renderer
    {
    public:
        Renderer();
        void init();

        void beginScene();
        void endScene();
        void submit(const std::weak_ptr<VertexArray>& vertexArray);
    };
}
