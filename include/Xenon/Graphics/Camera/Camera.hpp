#pragma once

#include "Xenon/Core/Api.hpp"

#include <glm/glm.hpp>

namespace Xenon
{
    class Camera
    {
    public:
        explicit Camera(const glm::mat4& projectionMatrix);
        virtual ~Camera() = default;

        virtual void setPosition(const glm::vec3& position);

        XN_NODISCARD virtual const glm::vec3& position() const;
        XN_NODISCARD virtual const glm::mat4& projectionMatrix() const;
        XN_NODISCARD virtual const glm::mat4& viewMatrix() const;
        XN_NODISCARD virtual const glm::mat4& viewProjectionMatrix() const;

    protected:
        virtual void calculateViewMatrix() = 0;

        glm::vec3 mPosition { 0.0f, 0.0f, 0.0f };
        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix{ 1.0f };
        glm::mat4 mViewProjectionMatrix;
    };
}