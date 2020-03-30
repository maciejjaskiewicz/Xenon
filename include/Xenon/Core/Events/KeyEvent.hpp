#pragma once

#include "../../Services/Event/Event.hpp"

#include <fmt/format.h>

namespace Xenon
{
    struct KeyEvent : Event
    {
        int keyCode;

    protected:
        explicit KeyEvent(const unsigned keyCode)
            : keyCode(keyCode)
        { }
    };

    struct KeyPressedEvent final : KeyEvent
    {
        bool repeat;

        explicit KeyPressedEvent(const int keyCode, const bool repeat)
            : KeyEvent(keyCode), repeat(repeat)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: Code={}, Repeat={}", Event::toString(), keyCode, repeat);
        }
    };

    struct KeyReleasedEvent final : KeyEvent
    {
        explicit KeyReleasedEvent(const int keyCode)
            : KeyEvent(keyCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: Code={}", Event::toString(), keyCode);
        }
    };

    struct KeyTypedEvent final : KeyEvent
    {
        explicit KeyTypedEvent(const int keyCode)
            : KeyEvent(keyCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: Code={}", Event::toString(), keyCode);
        }
    };
}