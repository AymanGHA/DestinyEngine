#include "Renderer.h"
#include "../Core/Log.h"
#include <GL/glew.h>

namespace Destiny {

Renderer::Renderer() {
    // Constructor vacío o inicialización si es necesario
}

Renderer::~Renderer() {
    // Liberar recursos si es necesario
}

bool Renderer::Initialize() {
    DESTINY_CORE_INFO("Inicializando renderer");

    // Obtener información de OpenGL
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);

    DESTINY_CORE_INFO("Información de OpenGL:");
    DESTINY_CORE_INFO("  Versión: " + std::string(reinterpret_cast<const char*>(version)));
    DESTINY_CORE_INFO("  Renderer: " + std::string(reinterpret_cast<const char*>(renderer)));
    DESTINY_CORE_INFO("  Vendor: " + std::string(reinterpret_cast<const char*>(vendor)));

    // Configuración de OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Renderer::Clear(const Color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Resetear estadísticas
    m_Stats = {};
}

void Renderer::BeginScene(const glm::mat4& projection, const glm::mat4& view) {
    m_ProjectionMatrix = projection;
    m_ViewMatrix = view;
}

void Renderer::EndScene() {
    // Procesar final de la escena si es necesario
}

void Renderer::DrawSprite(const std::shared_ptr<Sprite>& sprite, const glm::vec2& position, 
                          const glm::vec2& size, float rotation) {
    // Implementación para renderizar un sprite
    m_Stats.drawCalls++;
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, 
                        const Color& color, float rotation) {
    // Implementación para renderizar un quad con color
    m_Stats.drawCalls++;
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, 
                        const std::shared_ptr<Texture>& texture, float rotation) {
    // Implementación para renderizar un quad con textura
    m_Stats.drawCalls++;
}

const Renderer::Stats& Renderer::GetStats() const {
    return m_Stats;
}

} // namespace Destiny
