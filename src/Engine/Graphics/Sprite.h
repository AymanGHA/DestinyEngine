#pragma once

#include "Graphics/Texture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Destiny {

class Sprite {
public:
    Sprite(const std::shared_ptr<Texture>& texture);
    Sprite(const std::string& texturePath);
    ~Sprite() = default;

    // Renderizar el sprite
    void Draw(const glm::vec2& position, const glm::vec2& size = glm::vec2(1.0f), float rotation = 0.0f);
    
    // Establecer región de textura (para spritesheet)
    void SetTextureRegion(const glm::vec2& min, const glm::vec2& max);
    
    // Establecer color de tinte
    void SetColor(const glm::vec4& color) { m_Color = color; }
    const glm::vec4& GetColor() const { return m_Color; }
    
    // Acceso a la textura
    std::shared_ptr<Texture> GetTexture() const { return m_Texture; }

private:
    std::shared_ptr<Texture> m_Texture;
    glm::vec2 m_TexCoordMin = { 0.0f, 0.0f };
    glm::vec2 m_TexCoordMax = { 1.0f, 1.0f };
    glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f }; // Color blanco por defecto
    
    // Inicializar recursos de OpenGL
    void Init();
    
    // VAO y VBO para el cuadrado del sprite
    uint32_t m_VAO = 0;
    uint32_t m_VBO = 0;
    uint32_t m_IBO = 0; // Index Buffer Object
};

} // namespace Destiny