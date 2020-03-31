#pragma once

#include "../../Services/Event/Event.hpp"
#include "../Input/MouseCode.hpp"

#include <fmt/format.h>

namespace Xenon
{
    struct MouseButtonEvent : Event
    {
        MouseButtonCode buttonCode;

    protected:
        explicit MouseButtonEvent(const MouseButtonCode buttonCode)
            : buttonCode(buttonCode)
        { }
    };

    struct MouseButtonPressedEvent final : MouseButtonEvent
    {
        explicit MouseButtonPressedEvent(const MouseButtonCode buttonCode)
            : MouseButtonEvent(buttonCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: {}", Event::toString(), buttonCode);
        }
    };

    struct MouseButtonReleasedEvent final : MouseButtonEvent
    {
        explicit MouseButtonReleasedEvent(const MouseButtonCode buttonCode)
            : MouseButtonEvent(buttonCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: {}", Event::toString(), buttonCode);
        }
    };

    struct MouseMovedEvent final : Event
    {
        float x, y;

        explicit MouseMovedEvent(const float x, const float y)
            : x(x), y(y)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: X={}, Y={}", Event::toString(), x, y);
        }
    };

    struct MouseScrolledEvent final : Event
    {
        float xOffset, yOffset;

        explicit MouseScrolledEvent(const float xOffset, const float yOffset)
            : xOffset(xOffset), yOffset(yOffset)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: XOffset={}, YOffset={}", Event::toString(), xOffset, yOffset);
        }
    };
}