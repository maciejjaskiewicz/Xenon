#pragma once

#include "Xenon/Services/Event/Event.hpp"
#include "Xenon/Core/Input/KeyCode.hpp"

#include <fmt/format.h>

namespace Xenon
{
    struct KeyEvent : Event
    {
        KeyCode keyCode;

    protected:
        explicit KeyEvent(const KeyCode keyCode)
            : keyCode(keyCode)
        { }
    };

    struct KeyPressedEvent final : KeyEvent
    {
        bool repeat;

        explicit KeyPressedEvent(const KeyCode keyCode, const bool repeat)
            : KeyEvent(keyCode), repeat(repeat)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: Code={}, Repeat={}", Event::toString(), keyCode, repeat);
        }
    };

    struct KeyReleasedEvent final : KeyEvent
    {
        explicit KeyReleasedEvent(const KeyCode keyCode)
            : KeyEvent(keyCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: Code={}", Event::toString(), keyCode);
        }
    };

    struct KeyTypedEvent final : KeyEvent
    {
        explicit KeyTypedEvent(const KeyCode keyCode)
            : KeyEvent(keyCode)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: Code={}", Event::toString(), keyCode);
        }
    };
}