#pragma once

#include "../Core/Api.hpp"

namespace Xenon
{
    class DeltaTime
    {
    public:
        explicit DeltaTime(float initialTime);

        void update(float currentTime);

        XN_NODISCARD float seconds() const noexcept;
        XN_NODISCARD float milliseconds() const noexcept;

        operator float() const;

    private:
        float mLastFrameTime{ 0.0f };
        float mDeltaTime{ 0.0f };
    };
}