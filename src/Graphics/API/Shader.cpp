#include <Graphics/API/Shader.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

#include <fstream>
#include <filesystem>

namespace Xenon
{
    std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc,
        const std::string& fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
    }

    std::shared_ptr<Shader> ShaderLoader::load() const
    {
        const auto vertexSrc = readShaderFile(getArgs().vertexShaderPath);
        const auto fragmentSrc = readShaderFile(getArgs().fragmentShaderPath);

        return Shader::create(vertexSrc, fragmentSrc);
    }

    std::string ShaderLoader::readShaderFile(const std::string& path) const
    {
        const auto absolutePath = std::filesystem::canonical(path).string();
        std::ifstream fileHandler(path, std::ios::in | std::ios::binary);

        std::string shaderContent;

        if (fileHandler)
        {
            fileHandler.seekg(0, std::ios::end);
            const auto size = fileHandler.tellg();

            if (size != -1)
            {
                shaderContent.resize(size);
                fileHandler.seekg(0, std::ios::beg);
                fileHandler.read(&shaderContent[0], size);
                fileHandler.close();
            }
            else
            {
                XN_ENG_ERROR("Cannot read from shader file: {}", absolutePath);
            }
        }
        else
        {
            XN_ENG_ERROR("Cannot open shader file: {}", absolutePath);
        }

        XN_ENG_INFO("Shader file loaded: {}", absolutePath);
        return shaderContent;
    }
}
