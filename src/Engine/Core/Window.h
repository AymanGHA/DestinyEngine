#pragma once

#include <string>

// Para prevenir problemas, primero incluimos GL/glew.h
#include <GL/glew.h>
// Luego incluimos GLFW
#include <GLFW/glfw3.h>

namespace Destiny {

class Window {
public:
    Window(const std::string& title, int width, int height, bool vsync = true);
    ~Window();
    
    // No permitir copia
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    
    // Métodos de ventana
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose() const;
    
    // Información
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    bool IsVSync() const { return m_VSync; }
    bool IsValid() const { return m_Window != nullptr; }
    
    // Acceso a la ventana nativa
    GLFWwindow* GetNativeWindow() const { return m_Window; }

private:
    GLFWwindow* m_Window = nullptr;
    std::string m_Title;
    int m_Width;
    int m_Height;
    bool m_VSync;
    
    // Inicialización
    bool Init();
    void Shutdown();
};

} // namespace Destiny