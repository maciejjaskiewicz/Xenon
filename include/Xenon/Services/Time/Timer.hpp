#pragma once

#include "../../Core/Api.hpp"
#include <chrono>

namespace Xenon
{
    using HighResolutionClock = std::chrono::high_resolution_clock;
    using SystemClock = std::chrono::system_clock;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

    using Hours = std::chrono::hours;
    using Minutes = std::chrono::minutes;
    using Seconds = std::chrono::seconds;
    using Milliseconds = std::chrono::milliseconds;
    using Nanoseconds = std::chrono::nanoseconds;

    class Timer
    {
    public:
        explicit Timer()
            : mInitialTime(HighResolutionClock::now())
        { }

        template<typename TDuration = Seconds>
        XN_NODISCARD uint64_t now() const
        {
            using namespace std::chrono;

            const auto timeSinceEpoch = duration_cast<TDuration>(SystemClock::now().time_since_epoch());
            return timeSinceEpoch.count();
        }

        template<typename TResult = float>
        XN_NODISCARD TResult elapsed() const
        {
            using namespace std::chrono;
            return duration_cast<duration<TResult>>(HighResolutionClock::now() - mInitialTime).count();
        }

    private:
        TimePoint mInitialTime;
    };
}