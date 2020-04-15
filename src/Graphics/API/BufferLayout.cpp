#include <Graphics/API/BufferLayout.hpp>

namespace Xenon
{
    BufferLayout::BufferLayout() = default;

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
        : mElements(elements)
    {
        uint32_t offset = 0;

        for (auto& element : mElements)
        {
            element.offset = offset;
            offset += element.size;
            mStride += element.size;
        }
    }

    const std::vector<BufferElement>& BufferLayout::elements() const
    {
        return mElements;
    }

    uint32_t BufferLayout::stride() const noexcept
    {
        return mStride;
    }

    uint32_t BufferLayout::count() const noexcept
    {
        return static_cast<uint32_t>(mElements.size());
    }

    XN_NODISCARD std::vector<BufferElement>::iterator BufferLayout::begin()
    {
        return mElements.begin();
    }

    XN_NODISCARD std::vector<BufferElement>::iterator BufferLayout::end()
    {
        return mElements.end();
    }

    XN_NODISCARD std::vector<BufferElement>::const_iterator BufferLayout::begin() const
    {
        return mElements.begin();
    }

    XN_NODISCARD std::vector<BufferElement>::const_iterator BufferLayout::end() const
    {
        return mElements.end();
    }
}