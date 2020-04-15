#pragma once

#include "Camera.hpp"
#include "Xenon/Utils/DeltaTime.hpp"

namespace Xenon
{
    class CameraController
    {
    public:
        explicit CameraController(float aspectRation);
        virtual ~CameraController() = default;

        virtual void update(const DeltaTime& deltaTime) = 0;
        virtual void updateDebugGui(const Xenon::DeltaTime& deltaTime); // Camera debug window

        XN_NODISCARD virtual const Camera& camera() const = 0;
    protected:
        float mAspectRatio;
    };
}