#pragma once

#include "CameraController.hpp"
#include "OrthographicCamera.hpp"

namespace Xenon
{
    class OrthographicCameraController : public CameraController
    {
    public:
        explicit OrthographicCameraController(float aspectRatio, 
            bool rotation = false);

        void update(const DeltaTime& deltaTime) override;
        void updateDebugGui(const Xenon::DeltaTime& deltaTime) override;

        XN_NODISCARD const Camera& camera() const override;
    protected:
        float mZoomLevel{ 1.0f };
        glm::vec3 mCameraPosition{ 0.0f, 0.0f, 0.0f };
        float mCameraRotation{ 0.0f };

        float mCameraSpeed{ 3.0f };
        float mCameraRotationSpeed{ 180.0f };

        bool mRotation{ false };
        bool mLocked{ true };

        std::unique_ptr<OrthographicCamera> mCamera;
    private:
        XN_NODISCARD OrthographicCameraProjConfiguration calculateCameraProjConfiguration() const;
        void subscribeEvents();
    };
}