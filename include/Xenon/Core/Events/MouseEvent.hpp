#pragma once

#include "../../Services/Event/Event.hpp"

#include <fmt/format.h>

namespace Xenon
{
    struct MouseButtonEvent : Event
    {
        int buttonCode;

    protected:
        explicit MouseButtonEvent(const int buttonCode)
            : buttonCode(buttonCode)
        { }
    };

    struct MouseButtonPressedEvent final : MouseButtonEvent
    {
        explicit MouseButtonPressedEvent(const int buttonCode)
            : MouseButtonEvent(buttonCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: {}", Event::toString(), buttonCode);
        }
    };

    struct MouseButtonReleasedEvent final : MouseButtonEvent
    {
        explicit MouseButtonReleasedEvent(const int buttonCode)
            : MouseButtonEvent(buttonCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: {}", Event::toString(), buttonCode);
        }
    };

    struct MouseMovedEvent final : Event
    {
        double x, y;

        explicit MouseMovedEvent(const double x, const double y)
            : x(x), y(y)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: X={}, Y={}", Event::toString(), x, y);
        }
    };

    struct MouseScrolledEvent final : Event
    {
        double xOffset, yOffset;

        explicit MouseScrolledEvent(const double xOffset, const double yOffset)
            : xOffset(xOffset), yOffset(yOffset)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: XOffset={}, YOffset={}", Event::toString(), xOffset, yOffset);
        }
    };
}