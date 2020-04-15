#pragma once

#include "Xenon/Core/DataType.hpp"

namespace Xenon
{
    struct BufferElement
    {
        DataType type;
        std::string name;
        uint32_t size{};
        uint32_t offset{};
        bool normalized{};

        BufferElement(const DataType type, std::string name, const bool normalized = false)
            : type(type), name(std::move(name)), size(DataTypeInfo::size(type)),
              normalized(normalized)
        { }
    };

    class BufferLayout
    {
    public:
        BufferLayout();
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        XN_NODISCARD const std::vector<BufferElement>& elements() const;
        XN_NODISCARD uint32_t stride() const noexcept;
        XN_NODISCARD uint32_t count() const noexcept;

        XN_NODISCARD std::vector<BufferElement>::iterator begin();
        XN_NODISCARD std::vector<BufferElement>::iterator end();
        XN_NODISCARD std::vector<BufferElement>::const_iterator begin() const;
        XN_NODISCARD std::vector<BufferElement>::const_iterator end() const;
    private:
        std::vector<BufferElement> mElements;
        uint32_t mStride{};
    };
}