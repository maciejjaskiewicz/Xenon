#pragma once

#include <Graphics/API/IndexBuffer.hpp>

namespace Xenon
{
    class OpenGLIndexBuffer final : public IndexBuffer
    {
    public:
        explicit OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        void bind() const override;
        void unbind() const override;

        XN_NODISCARD uint32_t count() const noexcept override;

    private:
        uint32_t mIndexBufferId{};
        uint32_t mCount{};
    };
}