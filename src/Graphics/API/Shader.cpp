#include <Graphics/API/Shader.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Xenon
{
    std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc,
        const std::string& fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
    }
}