#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

namespace Xenon
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &mVertexArrayId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &mVertexArrayId);
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(mVertexArrayId);
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::pushVertexBuffer(std::weak_ptr<VertexBuffer> vertexBuffer)
    {
        constexpr auto toGLType = [](const DataType dataType) constexpr -> GLenum
        {
            switch (dataType)
            {
                case DataType::Bool:      return GL_BOOL;
                case DataType::Int:       return GL_INT;
                case DataType::Int2:      return GL_INT;
                case DataType::Int3:      return GL_INT;
                case DataType::Int4:      return GL_INT;
                case DataType::Float:     return GL_FLOAT;
                case DataType::Float2:    return GL_FLOAT;
                case DataType::Float3:    return GL_FLOAT;
                case DataType::Float4:    return GL_FLOAT;
                case DataType::Mat3:      return GL_FLOAT;
                case DataType::Mat4:      return GL_FLOAT;
            }

            XN_ASSERT_COM(false, "Unknown data type!");
            return 0;
        };

        if (const auto sVertexBuffer = vertexBuffer.lock())
        {
            XN_ASSERT_COM(sVertexBuffer->layout().count(), "Vertex Buffer has no layout!");

            bind();
            sVertexBuffer->bind();

            for (const auto& element : sVertexBuffer->layout())
            {
                glEnableVertexAttribArray(mVertexAttributeIdx);

                GLvoid const* offset = static_cast<char const*>(nullptr) + element.offset;
                const auto stride = static_cast<GLsizei>(sVertexBuffer->layout().stride());

                glVertexAttribPointer(
                    mVertexAttributeIdx,
                    static_cast<GLint>(DataTypeInfo::componentCount(element.type)),
                    toGLType(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    stride,
                    offset
                );

                mVertexAttributeIdx++;
            }
        }
        else
        {
            XN_ASSERT_COM(false, "Vertex Buffer expired!");
        }

        mVertexBuffers.push_back(std::move(vertexBuffer));
    }

    void OpenGLVertexArray::bindIndexBuffer(std::weak_ptr<IndexBuffer> indexBuffer)
    {
        if (const auto sIndexBuffer = indexBuffer.lock())
        {
            bind();
            sIndexBuffer->bind();
        }
        else
        {
            XN_ASSERT_COM(false, "Index Buffer expired!");
        }

        mIndexBuffer = std::move(indexBuffer);
    }

    XN_NODISCARD const IndexBuffer& OpenGLVertexArray::indexBuffer() const
    {
        if (mIndexBuffer.expired())
        {
            XN_ASSERT_COM(false, "Index Buffer expired!");
        }

        return *mIndexBuffer.lock();
    }
}