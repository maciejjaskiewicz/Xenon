#pragma once

#include "../Core/Api.hpp"
#include <glm/glm.hpp>

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
}