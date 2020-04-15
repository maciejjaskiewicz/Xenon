#pragma once

#include "Xenon/Services/Event/Event.hpp"
#include "Xenon/Core/Window/WindowResolution.hpp"

#include <fmt/format.h>

namespace Xenon
{
    struct WindowCloseEvent final : Event
    { };

    struct WindowResizeEvent final : Event
    {
        WindowResolution resolution;

        explicit WindowResizeEvent(const WindowResolution windowResolution)
            : resolution(windowResolution)
        { }

        XN_NODISCARD std::string toString() const override
        {
            return fmt::format("{}: {}x{}", Event::toString(), 
                resolution.width, resolution.height);
        }
    };
}