#pragma once

#include <Graphics/API/Shader.hpp>

namespace Xenon
{
    enum class ShaderType
    {
        Vertex,
        Fragment
    };

    class OpenGLShader final : public Shader
    {
    public:
        explicit OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        void setInt(const std::string& name, int value) const override;
        void setFloat(const std::string& name, float value) const override;
        void setFloat2(const std::string& name, const glm::vec2& value) const override;
        void setFloat3(const std::string& name, const glm::vec3& value) const override;
        void setFloat4(const std::string& name, const glm::vec4& value) const override;
        void setMat3(const std::string& name, const glm::mat3& value) const override;
        void setMat4(const std::string& name, const glm::mat4& value) const override;

    private:
        XN_NODISCARD uint32_t compileShader(ShaderType shaderType, const std::string& shaderSrc) const;
        XN_NODISCARD uint32_t linkShaderProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId) const;

        static std::string toString(ShaderType shaderType);
        static uint32_t toGlShaderType(ShaderType shaderType);

        uint32_t mShaderProgramId;
    };
}