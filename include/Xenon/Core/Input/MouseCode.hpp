#pragma once

#include <cstdint>

constexpr uint16_t XN_MOUSE_BUTTON_0 = 0;
constexpr uint16_t XN_MOUSE_BUTTON_1 = 1;
constexpr uint16_t XN_MOUSE_BUTTON_2 = 2;
constexpr uint16_t XN_MOUSE_BUTTON_3 = 3;
constexpr uint16_t XN_MOUSE_BUTTON_4 = 4;
constexpr uint16_t XN_MOUSE_BUTTON_5 = 5;
constexpr uint16_t XN_MOUSE_BUTTON_6 = 6;
constexpr uint16_t XN_MOUSE_BUTTON_7 = 7;
constexpr uint16_t XN_MOUSE_BUTTON_LAST = XN_MOUSE_BUTTON_7;
constexpr uint16_t XN_MOUSE_BUTTON_LEFT = XN_MOUSE_BUTTON_0;
constexpr uint16_t XN_MOUSE_BUTTON_RIGHT = XN_MOUSE_BUTTON_1;
constexpr uint16_t XN_MOUSE_BUTTON_MIDDLE = XN_MOUSE_BUTTON_2;

namespace Xenon
{
    enum class MouseButtonCode : uint16_t
    {
        Button0 = XN_MOUSE_BUTTON_0,
        Button1 = XN_MOUSE_BUTTON_1,
        Button2 = XN_MOUSE_BUTTON_2,
        Button3 = XN_MOUSE_BUTTON_3,
        Button4 = XN_MOUSE_BUTTON_4,
        Button5 = XN_MOUSE_BUTTON_5,
        Button6 = XN_MOUSE_BUTTON_6,
        Button7 = XN_MOUSE_BUTTON_7,

        ButtonLast = XN_MOUSE_BUTTON_LAST,
        ButtonLeft = XN_MOUSE_BUTTON_LEFT,
        ButtonRight = XN_MOUSE_BUTTON_RIGHT,
        ButtonMiddle = XN_MOUSE_BUTTON_MIDDLE
    };

    inline bool operator==(const MouseButtonCode mouseButtonCode, const uint16_t mouseButtonCodeInt)
    {
        return static_cast<uint16_t>(mouseButtonCode) == mouseButtonCodeInt;
    }
}