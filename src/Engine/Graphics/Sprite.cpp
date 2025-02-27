#include "Graphics/Sprite.h"
#include "Graphics/Shader.h"  // Necesitaremos esto para nuestro renderizado
#include "Core/Log.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Destiny {

Sprite::Sprite(const std::shared_ptr<Texture>& texture)
    : m_Texture(texture) {
    Init();
}

Sprite::Sprite(const std::string& texturePath)
    : m_Texture(std::make_shared<Texture>(texturePath)) {
    Init();
}

void Sprite::Init() {
    // Crear VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    // Crear VBO para vértices y coords de textura
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    // Los vértices se actualizarán en tiempo de renderizado
    // Por ahora, solo reservamos espacio
    float vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
    // Crear IBO (índices)
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    
    unsigned int indices[] = {
        0, 1, 2,  // Primer triángulo
        0, 3, 1   // Segundo triángulo
    };
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Configurar atributos de vértice
    // Posición
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    // Coordenadas de textura
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    // Desenlazar
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite::SetTextureRegion(const glm::vec2& min, const glm::vec2& max) {
    m_TexCoordMin = min;
    m_TexCoordMax = max;
}

void Sprite::Draw(const glm::vec2& position, const glm::vec2& size, float rotation) {
    // Aquí asumimos que tenemos un shader para sprites
    // En una implementación completa, necesitaríamos manejar esto adecuadamente
    static Shader* spriteShader = nullptr;
    
    if (!spriteShader) {
        // Crear un shader básico para sprites si no existe
        // Normalmente esto se haría en el sistema de recursos
        spriteShader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");
    }
    
    spriteShader->Bind();
    
    // Calcular matriz de modelo
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    
    // Rotar alrededor del centro del sprite
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    
    // Escalar
    model = glm::scale(model, glm::vec3(size, 1.0f));
    
    // Actualizar vértices con las coordenadas de textura adecuadas
    float vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, m_TexCoordMin.x, m_TexCoordMax.y,
        1.0f, 0.0f, m_TexCoordMax.x, m_TexCoordMin.y,
        0.0f, 0.0f, m_TexCoordMin.x, m_TexCoordMin.y,
        1.0f, 1.0f, m_TexCoordMax.x, m_TexCoordMax.y
    };
    
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    
    // Establecer uniforms
    spriteShader->SetMat4("u_Model", model);
    spriteShader->SetVec4("u_Color", m_Color);
    
    // Enlazar textura
    m_Texture->Bind();
    spriteShader->SetInt("u_Texture", 0); // Unidad de textura 0
    
    // Renderizar
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Limpiar estado
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    spriteShader->Unbind();
}

} // namespace Destiny