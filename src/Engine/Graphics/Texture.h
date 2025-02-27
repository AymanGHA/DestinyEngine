#pragma once

#include <string>

namespace Destiny {

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    // No permitir copia
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Activar la textura en una unidad específica (por defecto 0)
    void Bind(uint32_t slot = 0) const;
    
    // Desactivar la textura
    void Unbind() const;
    
    // Obtener dimensiones
    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }
    
    // Obtener ID de OpenGL
    uint32_t GetRendererID() const { return m_RendererID; }

private:
    uint32_t m_RendererID = 0;
    std::string m_Path;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    int m_Channels = 0;
};

} // namespace Destiny