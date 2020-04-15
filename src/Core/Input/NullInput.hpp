#pragma once

#include <Core/Input/Input.hpp>

namespace Xenon
{
    class NullInput final : public Input
    {
    public:
        XN_NODISCARD bool isKeyPressed(KeyCode key) const override
        {
            XN_ENG_WARN("Using null input service!");
            return false;
        };

        XN_NODISCARD bool isMouseButtonPressed(MouseButtonCode mouseButton) const override
        {
            XN_ENG_WARN("Using null input service!");
            return false;
        };

        XN_NODISCARD std::pair<float, float> mousePosition() const override
        {
            XN_ENG_WARN("Using null input service!");

            float x{}, y{};
            return std::make_pair(x, y);
        };
    };
}