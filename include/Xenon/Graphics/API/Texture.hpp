#pragma once

#include "Xenon/Core/Api.hpp"

#include <cstdint>

namespace Xenon
{
    enum class TextureFormat
    {
        RGB,
        RGBA
    };

    enum class TextureFilter
    {
        LINEAR,
        NEAREST
    };

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t slot = 0) = 0;

        XN_NODISCARD virtual uint32_t width() const = 0;
        XN_NODISCARD virtual uint32_t height() const = 0;
    };
}