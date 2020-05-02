#pragma once

#include <Graphics/API/FrameBuffer.hpp>

#include "OpenGLTexture2D.hpp"

namespace Xenon
{
    class OpenGLFrameBuffer final : public FrameBuffer
    {
    public:
        explicit OpenGLFrameBuffer(uint32_t width, uint32_t height);
        ~OpenGLFrameBuffer();

        void bind() const override;
        void unbind() const override;

        XN_NODISCARD const Texture& texture() const override;
    private:
        uint32_t mFrameBufferId{};
        uint32_t mDepthBufferId{};

        uint32_t mWidth;
        uint32_t mHeight;

        std::unique_ptr<OpenGLTexture2D> mTexture;
    };
}