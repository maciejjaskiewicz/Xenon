#pragma once

#include <Graphics/API/Texture2D.hpp>


namespace Xenon
{
    class OpenGLTexture2D final : public Texture2D
    {
    public:
        explicit OpenGLTexture2D(const void* pixels, const Texture2DConfiguration& configuration);
        explicit OpenGLTexture2D(const Texture2DConfiguration& configuration);
        ~OpenGLTexture2D();

        void init();

        void bind(uint32_t slot) override;
        void setData(const void* pixels, bool generateMipmap = true) override;

        XN_NODISCARD uint32_t id() const override;
        XN_NODISCARD uint32_t width() const override;
        XN_NODISCARD uint32_t height() const override;
    private:
        uint32_t mTextureId{};
        Texture2DConfiguration mConfiguration;
    };
}
