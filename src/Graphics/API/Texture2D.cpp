#include <Graphics/API/Texture2D.hpp>

#include "Platform/OpenGL/OpenGLTexture2D.hpp"

#include <filesystem>
#include <stb_image.h>

namespace Xenon
{
    std::shared_ptr<Texture2D> Texture2D::create(const void* pixels, const Texture2DConfiguration& configuration)
    {
        return std::make_shared<OpenGLTexture2D>(pixels, configuration);
    }

    std::shared_ptr<Texture2D> Texture2D::create(const Texture2DConfiguration& configuration)
    {
        return std::make_shared<OpenGLTexture2D>(configuration);
    }

    std::shared_ptr<Texture2D> Texture2DLoader::load() const
    {
        const auto args = getArgs();
        std::shared_ptr<Texture2D> texture;

        const auto absolutePath = std::filesystem::canonical(args.path).string();
        if(!std::filesystem::exists(absolutePath))
        {
            XN_ENG_ERROR("Texture file was not found: {}", absolutePath);
            return texture;
        }

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);

        stbi_uc* data = nullptr;
        data = stbi_load(absolutePath.c_str(), &width, &height, &channels, 0);
        if(!data)
        {
            XN_ENG_ERROR("Failed to load texture file: {}", absolutePath);
            return texture;
        }

        TextureFormat format;
        if(!tryParseFormat(channels, format))
        {
            XN_ENG_ERROR("Unsupported texture file format: {}", absolutePath);
            return texture;
        }

        const Texture2DConfiguration cfg(width, height, format, args.minFilter, args.maxFilter);
        texture = Texture2D::create(data, cfg);

        stbi_image_free(data);

        XN_ENG_INFO("Texture file loaded: {}", absolutePath);
        return texture;
    }

    bool Texture2DLoader::tryParseFormat(const int channels, TextureFormat& format)
    {
        auto valid = true;

        switch (channels)
        {
            case 3: format = TextureFormat::RGB; break;
            case 4: format = TextureFormat::RGBA; break;
            default: valid = false;
        }

        return valid;
    }
}
