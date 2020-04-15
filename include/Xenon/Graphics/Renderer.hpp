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
        void submit(const std::weak_ptr<Shader>& shader, const std::weak_ptr<VertexArray>& vertexArray) const;

        XN_NODISCARD const RendererAPIDetails& getDetails() const;
    private:
        glm::mat4 mViewProjectionMatrix{ 1.0f };
        RendererAPIDetails mAPIDetails;
    };
}