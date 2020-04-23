#include <Xenon/Graphics/Camera/OrthographicCameraController.hpp>

#include <Xenon/Core/ApplicationServices.hpp>
#include <Xenon/Core/Input/Input.hpp>
#include <Xenon/Core/Events/WindowEvent.hpp>
#include <Xenon/Core/Events/MouseEvent.hpp>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Xenon
{
    OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation)
        : CameraController(aspectRatio), mRotation(rotation)
    {
        const auto cameraConfiguration = calculateCameraProjConfiguration();
        mCamera = std::make_unique<OrthographicCamera>(cameraConfiguration);

        subscribeEvents();
    }

    void OrthographicCameraController::subscribeEvents()
    {
        ApplicationServices::EventBus::ref().subscribe<WindowResizeEvent>(
            [this](const WindowResizeEvent& event)
        {
            mAspectRatio = event.resolution.aspectRatio();
            mCamera->setProjection(calculateCameraProjConfiguration());
        });

        ApplicationServices::EventBus::ref().subscribe<MouseScrolledEvent>(
            [this](const MouseScrolledEvent& event)
        {
            if(mLocked) return;

            mZoomLevel -= event.yOffset * 0.25f;
            mZoomLevel = std::max(mZoomLevel, 0.1f);
            mCamera->setProjection(calculateCameraProjConfiguration());
        });
    }

    void OrthographicCameraController::update(const DeltaTime& deltaTime)
    {
        const auto& input = ApplicationServices::Input::ref();

        mLocked = !input.isKeyPressed(KeyCode::LeftControl);

        if(!mLocked)
        {
            const auto speed = mCameraSpeed * mZoomLevel * deltaTime;

            if(input.isKeyPressed(KeyCode::W))
            {
                mCameraPosition.x += static_cast<float>(-sin(glm::radians(mCameraRotation)) * speed);
                mCameraPosition.y += static_cast<float>(cos(glm::radians(mCameraRotation)) * speed);
            }

            if (input.isKeyPressed(KeyCode::S))
            {
                mCameraPosition.x -= static_cast<float>(-sin(glm::radians(mCameraRotation)) * speed);
                mCameraPosition.y -= static_cast<float>(cos(glm::radians(mCameraRotation)) * speed);
            }

            if (input.isKeyPressed(KeyCode::A))
            {
                mCameraPosition.x -= static_cast<float>(cos(glm::radians(mCameraRotation)) * speed);
                mCameraPosition.y -= static_cast<float>(sin(glm::radians(mCameraRotation)) * speed);
            }

            if (input.isKeyPressed(KeyCode::D))
            {
                mCameraPosition.x += static_cast<float>(cos(glm::radians(mCameraRotation)) * speed);
                mCameraPosition.y += static_cast<float>(sin(glm::radians(mCameraRotation)) * speed);
            }

            if(mRotation)
            {
                if (input.isKeyPressed(KeyCode::Q)) mCameraRotation += mCameraRotationSpeed * deltaTime;
                if (input.isKeyPressed(KeyCode::E)) mCameraRotation -= mCameraRotationSpeed * deltaTime;

                if (mCameraRotation > 180.0f) mCameraRotation -= 360.0f;
                else if (mCameraRotation <= -180.0f) mCameraRotation += 360.0f;

                mCamera->setRotation(mCameraRotation);
            }

            mCamera->setPosition(mCameraPosition);
        }
    }

    XN_NODISCARD const Camera& OrthographicCameraController::camera() const
    {
        return *mCamera;
    }

    OrthographicCameraProjConfiguration OrthographicCameraController::calculateCameraProjConfiguration() const
    {
        const OrthographicCameraProjConfiguration cameraConfiguration
        {
            -mAspectRatio * mZoomLevel,
            mAspectRatio * mZoomLevel,
            -mZoomLevel,
            mZoomLevel
        };

        return cameraConfiguration;
    }

    void OrthographicCameraController::updateDebugGui(const Xenon::DeltaTime& deltaTime)
    {
        ImGui::Begin("Orthographic Camera Debug");

        ImGui::InputFloat3("Position", glm::value_ptr(mCameraPosition));
        ImGui::InputFloat("Rotation", &mCameraRotation);
        ImGui::InputFloat("Zoom", &mZoomLevel);
        ImGui::Checkbox("Locked", &mLocked);

        ImGui::Separator();

        ImGui::SliderFloat("Speed", &mCameraSpeed, 1.0f, 10.0f);
        ImGui::SliderFloat("Rotation Speed", &mCameraRotationSpeed, 1.0f, 360.0f);

        ImGui::End();
    }
}