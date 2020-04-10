#pragma once

#include "BufferLayout.hpp"

namespace Xenon
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;

        XN_NODISCARD virtual const BufferLayout& layout() const = 0;

        XN_NODISCARD static std::shared_ptr<VertexBuffer> create(float* vertices, uint32_t size);
    };
}