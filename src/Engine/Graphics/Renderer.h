#pragma once

#include <array>
#include <memory>
#include <glm/glm.hpp>

namespace Destiny {

// Forward declarations
class Shader;
class Sprite;
class Texture;

// Color RGBA (0.0f - 1.0f)
struct Color {
    float r, g, b, a;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    // No permitir copia
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
    // Inicialización
    bool Initialize();
    
    // Comandos de renderizado básicos
    void Clear(const Color& color);
    
    // Comenzar y finalizar una escena
    void BeginScene(const glm::mat4& projection, const glm::mat4& view);
    void EndScene();
    
    // Métodos de renderizado
    void DrawSprite(const std::shared_ptr<Sprite>& sprite, const glm::vec2& position, 
                   const glm::vec2& size = glm::vec2(1.0f), float rotation = 0.0f);
    
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, 
                 const Color& color, float rotation = 0.0f);
    
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, 
                 const std::shared_ptr<Texture>& texture, float rotation = 0.0f);
    
    // Estadísticas
    struct Stats {
        unsigned int drawCalls = 0;
        unsigned int triangleCount = 0;
    };
    
    const Stats& GetStats

} // namespace Destiny