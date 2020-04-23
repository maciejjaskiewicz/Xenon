#pragma once

#include "Xenon/Core/Api.hpp"
#include "Xenon/Utils/ResourceCache.hpp"

#include <glm/glm.hpp>
#include <utility>

namespace Xenon
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setInt(const std::string& name, int value) const = 0;
        virtual void setFloat(const std::string& name, float value) const = 0;
        virtual void setFloat2(const std::string& name, const glm::vec2& value) const = 0;
        virtual void setFloat3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void setFloat4(const std::string& name, const glm::vec4& value) const = 0;
        virtual void setMat3(const std::string& name, const glm::mat3& value) const = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& value) const = 0;

        XN_NODISCARD static std::shared_ptr<Shader> create(
            const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    struct ShaderLoaderArgs : ResourceLoaderArgs
    {
        std::string vertexShaderPath;
        std::string fragmentShaderPath;

        ShaderLoaderArgs() = default;
        ShaderLoaderArgs(std::string vertexShaderPath, std::string fragmentShaderPath)
            : vertexShaderPath(std::move(vertexShaderPath)),
              fragmentShaderPath(std::move(fragmentShaderPath))
        {  }
    };

    class ShaderLoader final : public ResourceLoader<Shader, ShaderLoaderArgs>
    {
    public:
        XN_NODISCARD std::shared_ptr<Shader> load() const override;
    private:
        XN_NODISCARD std::string readShaderFile(const std::string& path) const;
    };
}