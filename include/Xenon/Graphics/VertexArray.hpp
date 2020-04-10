#pragma once

#include "../Core/Api.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Xenon
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void pushVertexBuffer(std::weak_ptr<VertexBuffer> vertexBuffer) = 0;
        virtual void bindIndexBuffer(std::weak_ptr<IndexBuffer> indexBuffer) = 0;

        XN_NODISCARD virtual const IndexBuffer& indexBuffer() const = 0;

        XN_NODISCARD static std::shared_ptr<VertexArray> create();
    };
}