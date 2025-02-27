#pragma once

#include <string>
#include <functional>

namespace Destiny {

// Tipos de eventos
enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// Categorías de eventos (para filtrado)
enum EventCategory {
    None = 0,
    EventCategoryApplication = (1 << 0),
    EventCategoryInput       = (1 << 1),
    EventCategoryKeyboard    = (1 << 2),
    EventCategoryMouse       = (1 << 3),
    EventCategoryMouseButton = (1 << 4)
};

// Clase base de evento
class Event {
public:
    virtual ~Event() = default;
    
    bool Handled = false;
    
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    
    // Verificar si el evento pertenece a una categoría
    bool IsInCategory(EventCategory category) {
        return GetCategoryFlags() & category;
    }
    
    virtual std::string ToString() const { return GetName(); }
};

// Dispatcher de eventos
class EventDispatcher {
public:
    EventDispatcher(Event& event)
        : m_Event(event) {
    }
    
    // F será deducido por el compilador
    template<typename T, typename F>
    bool Dispatch(const F& func) {
        if (m_Event.GetEventType() == T::GetStaticType()) {
            m_Event.Handled = func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }
    
private:
    Event& m_Event;
};

} // namespace Destiny