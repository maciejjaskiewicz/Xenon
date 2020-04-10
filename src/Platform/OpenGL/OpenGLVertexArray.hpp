#pragma once

#include <Xenon/Graphics/VertexArray.hpp>

namespace Xenon
{
    class OpenGLVertexArray final : public VertexArray
    {
    public:
        explicit OpenGLVertexArray();
        ~OpenGLVertexArray();

        void bind() const override;
        void unbind() const override;

        void pushVertexBuffer(std::weak_ptr<VertexBuffer> vertexBuffer) override;
        void bindIndexBuffer(std::weak_ptr<IndexBuffer> indexBuffer) override;

        XN_NODISCARD const IndexBuffer& indexBuffer() const override;
    private:
        uint32_t mVertexArrayId{};
        uint32_t mVertexAttributeIdx{};

        std::vector<std::weak_ptr<VertexBuffer>> mVertexBuffers;
        std::weak_ptr<IndexBuffer> mIndexBuffer;
    };
}