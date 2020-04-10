#include "OpenGLShader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Xenon
{
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        const auto vertexShader = compileShader(ShaderType::Vertex, vertexSrc);
        const auto fragmentShader = compileShader(ShaderType::Fragment, fragmentSrc);

        mShaderProgramId = linkShaderProgram(vertexShader, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(mShaderProgramId);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(mShaderProgramId);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::setInt(const std::string& name, const int value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::setFloat(const std::string& name, const float value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::setMat3(const std::string& name, const glm::mat3& value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) const
    {
        const auto location = glGetUniformLocation(mShaderProgramId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    uint32_t OpenGLShader::compileShader(const ShaderType shaderType, const std::string& shaderSrc) const
    {
        const auto shaderId = glCreateShader(toGlShaderType(shaderType));

        const auto* source = shaderSrc.c_str();
        glShaderSource(shaderId, 1, &source, nullptr);

        glCompileShader(shaderId);

        auto isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            auto maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shaderId);

            XN_ENG_ERROR("{} shader compilation failure!", toString(shaderType));
            XN_ENG_ERROR("{}", infoLog.data());

            XN_ASSERT(false);
            return 0;
        }

        return shaderId;
    }

    uint32_t OpenGLShader::linkShaderProgram(const uint32_t vertexShaderId, const uint32_t fragmentShaderId) const
    {
        const auto programId = glCreateProgram();

        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);

        glLinkProgram(programId);

        auto isLinked = 0;
        glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE)
        {
            auto maxLength = 0;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(programId);

            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);

            XN_ENG_ERROR("Shader linking error!");
            XN_ENG_ERROR("{}", infoLog.data());

            XN_ASSERT(false);
            return 0;
        }

        glDetachShader(programId, vertexShaderId);
        glDetachShader(programId, fragmentShaderId);

        return programId;
    }

    std::string OpenGLShader::toString(const ShaderType shaderType)
    {
        switch (shaderType)
        {
            case ShaderType::Vertex: return "Vertex";
            case ShaderType::Fragment: return "Fragment";
        }

        XN_ASSERT(false);
        return std::string("");
    }

    uint32_t OpenGLShader::toGlShaderType(const ShaderType shaderType)
    {
        switch (shaderType)
        {
            case ShaderType::Vertex: return GL_VERTEX_SHADER;
            case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
        }

        XN_ASSERT(false);
        return 0;
    }
}