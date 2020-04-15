#pragma once

#include <Graphics/API/VertexBuffer.hpp>

namespace Xenon
{
    class OpenGLVertexBuffer final : public VertexBuffer
    {
    public:
        explicit OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        void setLayout(const BufferLayout& layout) override;
        XN_NODISCARD const BufferLayout& layout() const override;
    private:
        uint32_t mVertexBufferId{};
        BufferLayout mLayout{};
    };
}