#pragma once

#include "API/RendererAPIDetails.hpp"
#include "API/VertexArray.hpp"
#include "API/Shader.hpp"
#include "Camera/Camera.hpp"

#include <glm/glm.hpp>

namespace Xenon
{
    class Renderer
    {
    public:
        Renderer();
        void init();

        void beginScene(const Camera& camera);
        void endScene();
        void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
            const glm::mat4& transform = glm::mat4(1.0f)) const;

        XN_NODISCARD const RendererAPIDetails& getDetails() const;
    private:
        glm::mat4 mViewProjectionMatrix{ 1.0f };
        RendererAPIDetails mAPIDetails;
    };
}