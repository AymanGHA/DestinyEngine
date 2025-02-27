#include "Graphics/Shader.h"
#include "Core/Log.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Destiny {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : m_VertPath(vertexPath), m_FragPath(fragmentPath) {
    
    std::string vertexSrc, fragmentSrc;
    
    try {
        vertexSrc = ReadFile(vertexPath);
        fragmentSrc = ReadFile(fragmentPath);
    }
    catch (const std::exception& e) {
        DESTINY_ERROR("Error al cargar shader: {0}", e.what());
        return;
    }
    
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    
    Compile(sources);
    
    DESTINY_INFO("Shader creado: Vertex={0}, Fragment={1}", vertexPath, fragmentPath);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

std::string Shader::ReadFile(const std::string& filepath) {
    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    
    if (in) {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else {
        DESTINY_ERROR("No se pudo abrir el archivo de shader: {0}", filepath);
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    
    return result;
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source) {
    std::unordered_map<GLenum, std::string> shaderSources;
    
    // Procesamiento de inclusiones, etc.
    // Por ahora, simplemente devolvemos el shader como está
    
    return shaderSources;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
    // Crear programa
    GLuint program = glCreateProgram();
    
    // Límite a 2 shaders por ahora
    std::vector<GLenum> glShaderIDs;
    glShaderIDs.reserve(2);
    
    // Compilar shaders
    for (auto& kv : shaderSources) {
        GLenum type = kv.first;
        const std::string& source = kv.second;
        
        // Crear shader
        GLuint shader = glCreateShader(type);
        
        // Establecer fuente
        const GLchar* sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, 0);
        
        // Compilar shader
        glCompileShader(shader);
        
        // Verificar errores
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            
            // El log debe incluir el carácter nulo
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
            
            // Liberar recursos
            glDeleteShader(shader);
            
            // Mostrar error
            DESTINY_ERROR("Error de compilación de shader!");
            DESTINY_ERROR("{0}", infoLog.data());
            
            // Fallo en la compilación
            throw std::runtime_error("Shader compilation failure!");
        }
        
        // Adjuntar shader al programa
        glAttachShader(program, shader);
        glShaderIDs.push_back(shader);
    }
    
    // Enlazar programa
    glLinkProgram(program);
    
    // Verificar errores de enlace
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        
        // El log debe incluir el carácter nulo
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        
        // Liberar recursos
        glDeleteProgram(program);
        for (auto id : glShaderIDs)
            glDeleteShader(id);
        
        // Mostrar error
        DESTINY_ERROR("Error de enlace de shader!");
        DESTINY_ERROR("{0}", infoLog.data());
        
        // Fallo en el enlace
        throw std::runtime_error("Shader link failure!");
    }
    
    // Desacoplar shaders después del enlace
    for (auto id : glShaderIDs) {
        glDetachShader(program, id);
        glDeleteShader(id);
    }
    
    m_RendererID = program;
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) const {
    // Buscar en cache
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    // Obtener ubicación
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        DESTINY_WARN("Uniform '{0}' no encontrado en shader", name);
    
    // Guardar en cache
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::SetInt(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetIntArray(const std::string& name, int* values, uint32_t count) {
    glUniform1iv(GetUniformLocation(name), count, values);
}

void Shader::SetFloat(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetFloat2(const std::string& name, const glm::vec2& value) {
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& value) {
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& value) {
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& matrix) {
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace Destiny