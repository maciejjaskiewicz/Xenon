#pragma once

#include "Texture.hpp"
#include "Xenon/Utils/ResourceCache.hpp"

namespace Xenon
{
    struct Texture2DConfiguration
    {
        uint32_t width;
        uint32_t height;
        TextureFormat format;
        TextureFilter minFilter;
        TextureFilter maxFilter;

        Texture2DConfiguration(const uint32_t width, const uint32_t height, const TextureFormat format, 
            const TextureFilter minFilter = TextureFilter::LINEAR, const TextureFilter maxFilter = TextureFilter::NEAREST)
            : width(width), height(height), format(format), minFilter(minFilter), maxFilter(maxFilter)
        { }
    };

    class Texture2D : public Texture
    {
    public:
        virtual void setData(const void* pixels) = 0;

        static std::shared_ptr<Texture2D> create(const void* pixels, const Texture2DConfiguration& configuration);
        static std::shared_ptr<Texture2D> create(const Texture2DConfiguration& configuration);
    };

    struct Texture2DLoaderArgs : ResourceLoaderArgs
    {
        std::string path;
        TextureFilter minFilter{ TextureFilter::LINEAR };
        TextureFilter maxFilter{ TextureFilter::NEAREST };

        Texture2DLoaderArgs() = default;
        Texture2DLoaderArgs(std::string path, const TextureFilter minFilter = TextureFilter::LINEAR, 
            const TextureFilter maxFilter = TextureFilter::NEAREST)
            : path(std::move(path)), minFilter(minFilter), maxFilter(maxFilter)
        {  }
    };

    class Texture2DLoader final : public ResourceLoader<Texture2D, Texture2DLoaderArgs>
    {
    public:
        XN_NODISCARD std::shared_ptr<Texture2D> load() const override;
    private:
        XN_NODISCARD static bool tryParseFormat(int channels, TextureFormat& format);
    };

}