#include <Xenon/Graphics/Camera/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace Xenon
{
    OrthographicCamera::OrthographicCamera(const OrthographicCameraProjConfiguration projectionConfiguration)
        : Camera(calculateProjectionMatrix(projectionConfiguration))
    { }

    void OrthographicCamera::setProjection(const OrthographicCameraProjConfiguration projectionConfiguration)
    {
        mProjectionMatrix = calculateProjectionMatrix(projectionConfiguration);
        calculateViewMatrix();
    }

    void OrthographicCamera::setRotation(const float rotation) noexcept
    {
        mRotation = rotation;
        calculateViewMatrix();
    }

    float OrthographicCamera::rotation() const noexcept
    {
        return mRotation;
    }

    void OrthographicCamera::calculateViewMatrix()
    {
        glm::mat4 view = glm::translate(glm::mat4(1.0f), mPosition);
        view = glm::rotate(view, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));

        mViewMatrix = glm::inverse(view);
        mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
    }

    glm::mat4 OrthographicCamera::calculateProjectionMatrix(const OrthographicCameraProjConfiguration projectionConfiguration) const
    {
        return glm::ortho(
            projectionConfiguration.left,
            projectionConfiguration.right,
            projectionConfiguration.bottom,
            projectionConfiguration.top,
            -1.0f,
            1.0f
        );
    }
}
