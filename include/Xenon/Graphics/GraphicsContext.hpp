#pragma once

#include "../Core/Api.hpp"

namespace Xenon
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void init() = 0;
        virtual void swapBuffers() = 0;

        XN_NODISCARD static std::unique_ptr<GraphicsContext> create(void* window);
    };
}
