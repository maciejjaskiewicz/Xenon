#include "OpenGLTexture2D.hpp"

#include <glad/glad.h>

namespace Xenon
{
    static constexpr GLenum toGlFormat(const TextureFormat format);
    static constexpr GLenum toGlInternalFormat(const TextureFormat format);
    static constexpr GLenum toGlFilter(const TextureFilter filter);
    static constexpr GLenum toGlWrap(const TextureWrap wrap);

    OpenGLTexture2D::OpenGLTexture2D(const void* pixels, const Texture2DConfiguration& configuration)
        : mConfiguration(configuration)
    {
        init();
        setData(pixels);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::OpenGLTexture2D(const Texture2DConfiguration& configuration)
        : mConfiguration(configuration)
    {
        init();

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &mTextureId);
    }

    void OpenGLTexture2D::init()
    {
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGlWrap(mConfiguration.wrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGlWrap(mConfiguration.wrap));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGlFilter(mConfiguration.minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGlFilter(mConfiguration.maxFilter));
    }

    void OpenGLTexture2D::bind(const uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
    }

    void OpenGLTexture2D::setData(const void* pixels, const bool generateMipmap)
    {
        const auto dataFormat = toGlFormat(mConfiguration.format);
        const auto internalFormat = toGlInternalFormat(mConfiguration.format);

        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mConfiguration.width, mConfiguration.height, 0, 
            dataFormat, GL_UNSIGNED_BYTE, pixels);

        if(generateMipmap)
            glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t OpenGLTexture2D::id() const
    {
        return mTextureId;
    }

    uint32_t OpenGLTexture2D::width() const
    {
        return mConfiguration.width;
    }

    uint32_t OpenGLTexture2D::height() const
    {
        return mConfiguration.height;
    }

    constexpr GLenum toGlFormat(const TextureFormat format)
    {
        switch (format)
        {
            case TextureFormat::RGB: return GL_RGB;
            case TextureFormat::RGBA: return GL_RGBA;
        }

        return 0;
    }

    constexpr GLenum toGlInternalFormat(const TextureFormat format)
    {
        switch (format)
        {
            case TextureFormat::RGB: return GL_RGB8;
            case TextureFormat::RGBA: return GL_RGBA8;
        }

        return 0;
    }

    constexpr GLenum toGlFilter(const TextureFilter filter)
    {
        switch (filter)
        {
            case TextureFilter::LINEAR: return GL_LINEAR;
            case TextureFilter::NEAREST: return GL_NEAREST;
        }

        return 0;
    }

    constexpr GLenum toGlWrap(const TextureWrap wrap)
    {
        switch (wrap)
        {
            case TextureWrap::REPEAT: return GL_REPEAT;
            case TextureWrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
            case TextureWrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
            case TextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
        }

        return 0;
    }
}
