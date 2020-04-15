#include <Xenon/Graphics/Camera/Camera.hpp>

namespace Xenon
{
    Camera::Camera(const glm::mat4& projectionMatrix)
        : mProjectionMatrix(projectionMatrix),
          mViewProjectionMatrix(mProjectionMatrix * mViewMatrix)
    { }

    void Camera::setPosition(const glm::vec3& position)
    {
        mPosition = position;
        calculateViewMatrix();
    }

    const glm::vec3& Camera::position() const
    {
        return mPosition;
    }

    const glm::mat4& Camera::projectionMatrix() const
    {
        return mProjectionMatrix;
    }

    const glm::mat4& Camera::viewMatrix() const
    {
        return mViewMatrix;
    }

    const glm::mat4& Camera::viewProjectionMatrix() const
    {
        return mViewProjectionMatrix;
    }
}
