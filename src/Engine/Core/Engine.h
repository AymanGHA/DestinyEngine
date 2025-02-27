#pragma once

#include <memory>
#include <string>
#include "Window.h"
#include "../Graphics/Renderer.h"

namespace Destiny {

class Engine {
public:
    struct Config {
        // En lugar de inicializadores por defecto, usamos valores inicializados en el constructor
        std::string appName;
        int width;
        int height;
        bool vsync;
        
        // Constructor por defecto con valores predefinidos
        Config() 
            : appName("Destiny Engine App"), width(1280), height(720), vsync(true) {}
    };

    Engine(const Config& config = Config());
    ~Engine();

    // No permitir copia
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    // Iniciar el motor
    bool Initialize();
    
    // Ciclo principal
    void Run();
    
    // Cerrar el motor
    void Shutdown();
    
    // Acceso a componentes
    Window& GetWindow() { return *m_Window; }
    Renderer& GetRenderer() { return *m_Renderer; }
    
    // Instancia global
    static Engine& Get() { return *s_Instance; }

private:
    bool m_Running = false;
    float m_LastFrameTime = 0.0f;
    
    Config m_Config;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
    
    // Para acceso global
    static Engine* s_Instance;
};

} // namespace Destiny