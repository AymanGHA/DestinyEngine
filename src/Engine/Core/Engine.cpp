#include "Engine.h"
#include "Log.h"

#include <GL/glew.h>  // GLEW primero
#include <GLFW/glfw3.h>

namespace Destiny {

// Inicializar la instancia estática
Engine* Engine::s_Instance = nullptr;

Engine::Engine(const Config& config)
    : m_Config(config) {
    // Establecer instancia global
    s_Instance = this;
    
    // Inicializar el sistema de log
    Log::Init();
    DESTINY_CORE_INFO("Creando motor: " + m_Config.appName);
}

Engine::~Engine() {
    DESTINY_CORE_INFO("Destruyendo motor");
    Shutdown();
    s_Instance = nullptr;
}

bool Engine::Initialize() {
    DESTINY_CORE_INFO("Inicializando motor");
    
    // Crear ventana
    m_Window = std::make_unique<Window>(m_Config.appName, m_Config.width, m_Config.height, m_Config.vsync);
    if (!m_Window->IsValid()) {
        DESTINY_CORE_ERROR("No se pudo crear la ventana");
        return false;
    }
    
    // Inicializar renderer
    m_Renderer = std::make_unique<Renderer>();
    if (!m_Renderer->Initialize()) {
        DESTINY_CORE_ERROR("No se pudo inicializar el renderer");
        return false;
    }
    
    m_Running = true;
    m_LastFrameTime = 0.0f;
    
    DESTINY_CORE_INFO("Motor inicializado correctamente");
    return true;
}

void Engine::Run() {
    DESTINY_CORE_INFO("Iniciando bucle principal");
    
    while (m_Running && !m_Window->ShouldClose()) {
        // Calcular tiempo delta
        float time = static_cast<float>(glfwGetTime());
        float deltaTime = time - m_LastFrameTime;
        m_LastFrameTime = time;
        
        // Limpiar pantalla con color azul oscuro
        m_Renderer->Clear({ 0.1f, 0.1f, 0.2f, 1.0f });
        
        // Aquí se implementaría la lógica de actualización y renderizado
        
        // Intercambiar buffers y procesar eventos
        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
    
    DESTINY_CORE_INFO("Bucle principal finalizado");
}

void Engine::Shutdown() {
    if (!m_Running) {
        return;
    }
    
    DESTINY_CORE_INFO("Apagando motor");
    
    // Liberar recursos en orden inverso
    m_Renderer.reset();
    m_Window.reset();
    
    m_Running = false;
}

} // namespace Destiny