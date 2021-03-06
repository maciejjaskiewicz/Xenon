#pragma once

#include "Xenon/Core/Api.hpp"

#include <cstdint>

namespace Xenon
{
    struct WindowResolution
    {
        uint32_t width;
        uint32_t height;

        explicit WindowResolution(const uint32_t windowWidth = 1280,
            const uint32_t windowHeight = 720) : width(windowWidth), height(windowHeight)
        { }

        XN_NODISCARD float aspectRatio() const
        {
            if(width == 0 || height == 0) return 0.0f;
            return static_cast<float>(width) / static_cast<float>(height);
        }

        friend bool operator== (const WindowResolution& lhs, const WindowResolution& rhs);
        friend bool operator!= (const WindowResolution& lhs, const WindowResolution& rhs);
    };

    inline bool operator==(const WindowResolution& lhs, const WindowResolution& rhs)
    {
        return lhs.width == rhs.width && lhs.height == rhs.height;
    }

    inline bool operator!=(const WindowResolution& lhs, const WindowResolution& rhs)
    {
        return !(lhs == rhs);
    }

    /*
     *  Convention:
     *  A - aspect ration, eg. 4x3, 16x9
     *  R - resolution, eg. 640x480
     */
    struct StandardWindowResolution
    {
        inline static const WindowResolution A_4X3_R_640X480 = WindowResolution(640, 480);
        inline static const WindowResolution A_4X3_R_1024X768 = WindowResolution(1024, 768);
        inline static const WindowResolution A_4X3_R_1600X1200 = WindowResolution(1600, 1200);
        inline static const WindowResolution A_4X3_R_1920X1440 = WindowResolution(1920, 1440);

        inline static const WindowResolution A_16X9_R_1024X576 = WindowResolution(1024, 576);
        inline static const WindowResolution A_16X9_R_1280X720 = WindowResolution(1280, 720);
        inline static const WindowResolution A_16X9_R_1366X768 = WindowResolution(1366, 768);
        inline static const WindowResolution A_16X9_R_1920X1080 = WindowResolution(1920, 1080);
    };
}
