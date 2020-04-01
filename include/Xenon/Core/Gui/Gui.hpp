#pragma once

#include "../Api.hpp"
#include "../Window/Window.hpp"

namespace Xenon
{
    class Gui
    {
    public:
        virtual ~Gui() = default;

        virtual void newFrame() const = 0;
        virtual void render() const = 0;

        XN_NODISCARD static std::unique_ptr<Gui> create(Window& window);
    };
}
