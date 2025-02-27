#include "Window.h"
#include "Log.h"

// Es crucial incluir GLEW antes que GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Destiny {

// Callback para errores de GLFW
static void GLFWErrorCallback(int error, const char* description) {
    DESTINY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window::Window(const std::string& title, int width, int height, bool vsync)
    : m_Title(title), m_Width(width), m_Height(height), m_VSync(vsync) {
    if (!Init()) {
        DESTINY_CORE_ERROR("No se pudo inicializar la ventana");
    }
}

Window::~Window() {
    Shutdown();
}

bool Window::Init() {
    DESTINY_CORE_INFO("Creando ventana: {0} ({1}x{2})", m_Title, m_Width, m_Height);
    
    // Inicializar GLFW
    if (!glfwInit()) {
        DESTINY_CORE_ERROR("No se pudo inicializar GLFW");
        return false;
    }
    
    // Configurar callback de error
    glfwSetErrorCallback(GLFWErrorCallback);
    
    // Configurar opciones de GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Crear ventana
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        DESTINY_CORE_ERROR("No se pudo crear la ventana GLFW");
        glfwTerminate();
        return false;
    }
    
    // Hacer contexto actual para OpenGL
    glfwMakeContextCurrent(m_Window);
    
    // Inicializar GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        DESTINY_CORE_ERROR("No se pudo inicializar GLEW: {0}", (const char*)glewGetErrorString(err));
        return false;
    }
    
    // Configurar VSync
    glfwSwapInterval(m_VSync ? 1 : 0);
    
    DESTINY_CORE_INFO("Ventana creada correctamente: {0} ({1}x{2})", m_Title, m_Width, m_Height);
    return true;
}

void Window::Shutdown() {
    if (m_Window) {
        DESTINY_CORE_INFO("Destruyendo ventana");
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

} // namespace Destiny