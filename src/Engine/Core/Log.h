#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace Destiny {

class Log {
public:
    static void Init() {
        std::cout << "Sistema de logs inicializado" << std::endl;
    }
    
    // Funciones básicas de log
    static void CoreTrace(const std::string& message) {
        std::cout << "[CORE] [TRACE] " << message << std::endl;
    }
    
    static void CoreInfo(const std::string& message) {
        std::cout << "[CORE] [INFO] " << message << std::endl;
    }
    
    static void CoreWarn(const std::string& message) {
        std::cout << "[CORE] [WARN] " << message << std::endl;
    }
    
    static void CoreError(const std::string& message) {
        std::cerr << "[CORE] [ERROR] " << message << std::endl;
    }
    
    static void CoreCritical(const std::string& message) {
        std::cerr << "[CORE] [CRITICAL] " << message << std::endl;
    }
    
    static void Trace(const std::string& message) {
        std::cout << "[APP] [TRACE] " << message << std::endl;
    }
    
    static void Info(const std::string& message) {
        std::cout << "[APP] [INFO] " << message << std::endl;
    }
    
    static void Warn(const std::string& message) {
        std::cout << "[APP] [WARN] " << message << std::endl;
    }
    
    static void Error(const std::string& message) {
        std::cerr << "[APP] [ERROR] " << message << std::endl;
    }
    
    static void Critical(const std::string& message) {
        std::cerr << "[APP] [CRITICAL] " << message << std::endl;
    }
    
    // Función auxiliar para formatear string
    template<typename T>
    static std::string Format(const std::string& format, T arg) {
        std::string result = format;
        size_t pos = result.find("{0}");
        if (pos != std::string::npos) {
            std::ostringstream ss;
            ss << arg;
            result.replace(pos, 3, ss.str());
        }
        return result;
    }
    
    // Versión recursiva para formatear múltiples argumentos
    template<typename T, typename... Args>
    static std::string Format(const std::string& format, T arg, Args... args) {
        std::string result = format;
        
        // Buscar el próximo marcador {n}
        for (int i = 0; i < 10; i++) {  // Soportamos hasta {9}
            std::string placeholder = "{" + std::to_string(i) + "}";
            size_t pos = result.find(placeholder);
            if (pos != std::string::npos) {
                std::ostringstream ss;
                ss << arg;
                result.replace(pos, placeholder.length(), ss.str());
                break;
            }
        }
        
        // Continuar con el resto de argumentos
        return Format(result, args...);
    }
    
    // Función base para terminar la recursión
    static std::string Format(const std::string& format) {
        return format;
    }
    
    // Métodos para múltiples argumentos - Core
    template<typename... Args>
    static void CoreInfo(const std::string& format, Args... args) {
        CoreInfo(Format(format, args...));
    }
    
    template<typename... Args>
    static void CoreWarn(const std::string& format, Args... args) {
        CoreWarn(Format(format, args...));
    }
    
    template<typename... Args>
    static void CoreError(const std::string& format, Args... args) {
        CoreError(Format(format, args...));
    }
    
    template<typename... Args>
    static void CoreCritical(const std::string& format, Args... args) {
        CoreCritical(Format(format, args...));
    }
    
    // Métodos para múltiples argumentos - App
    template<typename... Args>
    static void Trace(const std::string& format, Args... args) {
        Trace(Format(format, args...));
    }
    
    template<typename... Args>
    static void Info(const std::string& format, Args... args) {
        Info(Format(format, args...));
    }
    
    template<typename... Args>
    static void Warn(const std::string& format, Args... args) {
        Warn(Format(format, args...));
    }
    
    template<typename... Args>
    static void Error(const std::string& format, Args... args) {
        Error(Format(format, args...));
    }
    
    template<typename... Args>
    static void Critical(const std::string& format, Args... args) {
        Critical(Format(format, args...));
    }
};

} // namespace Destiny

// Macros de log del núcleo
#define DESTINY_CORE_TRACE(...)    ::Destiny::Log::CoreTrace(__VA_ARGS__)
#define DESTINY_CORE_INFO(...)     ::Destiny::Log::CoreInfo(__VA_ARGS__)
#define DESTINY_CORE_WARN(...)     ::Destiny::Log::CoreWarn(__VA_ARGS__)
#define DESTINY_CORE_ERROR(...)    ::Destiny::Log::CoreError(__VA_ARGS__)
#define DESTINY_CORE_CRITICAL(...) ::Destiny::Log::CoreCritical(__VA_ARGS__)

// Macros de log de la aplicación cliente
#define DESTINY_TRACE(...)    ::Destiny::Log::Trace(__VA_ARGS__)
#define DESTINY_INFO(...)     ::Destiny::Log::Info(__VA_ARGS__)
#define DESTINY_WARN(...)     ::Destiny::Log::Warn(__VA_ARGS__)
#define DESTINY_ERROR(...)    ::Destiny::Log::Error(__VA_ARGS__)
#define DESTINY_CRITICAL(...) ::Destiny::Log::Critical(__VA_ARGS__)