#include <Graphics/API/VertexArray.hpp>

#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Xenon
{
    XN_NODISCARD std::shared_ptr<VertexArray> VertexArray::create()
    {
        return std::make_shared<OpenGLVertexArray>();
    }
}