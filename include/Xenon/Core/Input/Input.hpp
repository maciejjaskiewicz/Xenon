#pragma once

#include "KeyCode.hpp"
#include "MouseCode.hpp"
#include "Xenon/Core/Window/Window.hpp"

#include <utility>
#include <memory>

namespace Xenon
{
    class Input
    {
    public:
        virtual ~Input() = default;

        XN_NODISCARD virtual bool isKeyPressed(KeyCode key) const = 0;
        XN_NODISCARD virtual bool isMouseButtonPressed(MouseButtonCode mouseButton) const = 0;

        XN_NODISCARD virtual std::pair<float, float> mousePosition() const = 0;

        XN_NODISCARD static std::unique_ptr<Input> create(Window& window);
    };
}
