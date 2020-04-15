#pragma once

#include "Camera.hpp"

namespace Xenon
{
    struct OrthographicCameraProjConfiguration
    {
        float left;
        float right;
        float bottom;
        float top;
    };

    class OrthographicCamera final : public Camera
    {
    public:
        explicit OrthographicCamera(OrthographicCameraProjConfiguration projectionConfiguration);

        void setProjection(OrthographicCameraProjConfiguration projectionConfiguration);
        void setRotation(float rotation) noexcept;
        XN_NODISCARD float rotation() const noexcept;
    private:
        void calculateViewMatrix() override;
        XN_NODISCARD glm::mat4 calculateProjectionMatrix(OrthographicCameraProjConfiguration projectionConfiguration) const;

        float mRotation{ 0.0f };
    };
}