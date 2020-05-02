#include "OpenGLFrameBuffer.hpp"
#include "OpenGLTexture2D.hpp"

#include <glad/glad.h>

namespace Xenon
{
    OpenGLFrameBuffer::OpenGLFrameBuffer(const uint32_t width, const uint32_t height)
        : mWidth(width), mHeight(height)
    {
        glGenFramebuffers(1, &mFrameBufferId);
        glGenRenderbuffers(1, &mDepthBufferId);

        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthBufferId);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mWidth, mHeight);

        const Texture2DConfiguration textureConfiguration(
            mWidth,
            mHeight,
            TextureFormat::RGBA,
            TextureFilter::LINEAR,
            TextureFilter::LINEAR,
            TextureWrap::CLAMP_TO_EDGE
        );
        mTexture = std::make_unique<OpenGLTexture2D>(textureConfiguration);
        mTexture->setData(nullptr, false);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture->id(), 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBufferId);

        XN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &mFrameBufferId);
        glDeleteRenderbuffers(1, &mDepthBufferId);
    }

    void OpenGLFrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
        glViewport(0, 0, mWidth, mHeight);
    }

    void OpenGLFrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    const Texture& OpenGLFrameBuffer::texture() const
    {
        return *mTexture;
    }
}