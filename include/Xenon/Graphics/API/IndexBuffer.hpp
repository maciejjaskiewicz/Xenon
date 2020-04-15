#pragma once

#include "Xenon/Core/Api.hpp"

namespace Xenon
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        XN_NODISCARD virtual uint32_t count() const noexcept = 0;

        XN_NODISCARD static std::shared_ptr<IndexBuffer> create(uint32_t* indices, uint32_t count);
    };
}
