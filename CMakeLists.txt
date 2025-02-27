cmake_minimum_required(VERSION 3.10)
project(DestinyEngine VERSION 0.1.0 LANGUAGES CXX)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Establecer preferencia de OpenGL
set(OpenGL_GL_PREFERENCE GLVND)

# Dependencias
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Directorios de inclusión
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Definir los archivos fuente
set(SOURCES
    src/main.cpp
    src/Engine/Core/Engine.cpp
    src/Engine/Core/Window.cpp
    src/Engine/Graphics/Renderer.cpp
)

# Crear un ejecutable
add_executable(DestinyApp ${SOURCES})

# Vincular dependencias
target_link_libraries(DestinyApp
    PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
)