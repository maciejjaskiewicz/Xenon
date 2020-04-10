#pragma once

#include "Api.hpp"

namespace Xenon
{
    enum class DataType
    {
        Bool,
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4,
        Mat3, Mat4
    };

    struct DataTypeInfo
    {
        static constexpr uint32_t componentCount(const DataType dataType)
        {
            switch (dataType)
            {
                case DataType::Bool:      return 1;
                case DataType::Int:       return 1;
                case DataType::Int2:      return 2;
                case DataType::Int3:      return 3;
                case DataType::Int4:      return 4;
                case DataType::Float:     return 1;
                case DataType::Float2:    return 2;
                case DataType::Float3:    return 3;
                case DataType::Float4:    return 4;
                case DataType::Mat3:      return 3 * 3;
                case DataType::Mat4:      return 4 * 4;
            }

            XN_ASSERT_COM(false, "Unknown data type!");
            return 0;
        }

        static constexpr uint32_t size(const DataType dataType)
        {
            switch (dataType)
            {
                case DataType::Bool:      return 1 * componentCount(DataType::Bool);
                case DataType::Int:       return 4 * componentCount(DataType::Int);
                case DataType::Int2:      return 4 * componentCount(DataType::Int2);
                case DataType::Int3:      return 4 * componentCount(DataType::Int3);
                case DataType::Int4:      return 4 * componentCount(DataType::Int4);
                case DataType::Float:     return 4 * componentCount(DataType::Float);
                case DataType::Float2:    return 4 * componentCount(DataType::Float2);
                case DataType::Float3:    return 4 * componentCount(DataType::Float3);
                case DataType::Float4:    return 4 * componentCount(DataType::Float4);
                case DataType::Mat3:      return 4 * componentCount(DataType::Mat3);
                case DataType::Mat4:      return 4 * componentCount(DataType::Mat4);
            }

            XN_ASSERT_COM(false, "Unknown data type!");
            return 0;
        }
    };
}