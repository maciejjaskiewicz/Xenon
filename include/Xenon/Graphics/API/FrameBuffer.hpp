#pragma once

#include "Xenon/Core/Api.hpp"
#include "Texture.hpp"

namespace Xenon
{
    class FrameBuffer
    {
    public:
        virtual ~FrameBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        XN_NODISCARD virtual const Texture& texture() const = 0;

        XN_NODISCARD static std::shared_ptr<FrameBuffer> create(uint32_t width, uint32_t height);
    };
}