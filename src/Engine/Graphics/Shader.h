#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Destiny {

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // No permitir copia
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // Activar/desactivar el shader
    void Bind() const;
    void Unbind() const;
    
    // Establecer uniforms
    void SetInt(const std::string& name, int value);
    void SetIntArray(const std::string& name, int* values, uint32_t count);
    void SetFloat(const std::string& name, float value);
    void SetFloat2(const std::string& name, const glm::vec2& value);
    void SetFloat3(const std::string& name, const glm::vec3& value);
    void SetFloat4(const std::string& name, const glm::vec4& value);
    void SetMat3(const std::string& name, const glm::mat3& matrix);
    void SetMat4(const std::string& name, const glm::mat4& matrix);
    
    // Getters
    uint32_t GetRendererID() const { return m_RendererID; }

private:
    std::string ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    
    uint32_t m_RendererID = 0;
    std::string m_VertPath, m_FragPath;
    
    // Cache para ubicaciones de uniforms
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
    int GetUniformLocation(const std::string& name) const;
};

} // namespace Destiny