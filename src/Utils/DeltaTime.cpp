#include <Utils/DeltaTime.hpp>

namespace Xenon
{
    DeltaTime::DeltaTime(const float initialTime)
        : mLastFrameTime(initialTime)
    { }

    void DeltaTime::update(const float currentTime)
    {
        mDeltaTime = currentTime - mLastFrameTime;
        mLastFrameTime = currentTime;
    }

    float DeltaTime::seconds() const noexcept
    {
        return mDeltaTime;
    }

    float DeltaTime::milliseconds() const noexcept
    {
        return mDeltaTime * 1000.0f;
    }

    DeltaTime::operator float() const
    {
        return mDeltaTime;
    }
}
