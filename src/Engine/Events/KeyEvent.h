#pragma once

#include "Event.h"
#include <sstream>

namespace Destiny {

// Evento base para teclado
class KeyEvent : public Event {
public:
    int GetKeyCode() const { return m_KeyCode; }
    
    int GetCategoryFlags() const override {
        return EventCategoryKeyboard | EventCategoryInput;
    }
    
protected:
    KeyEvent(int keycode)
        : m_KeyCode(keycode) {
    }
    
    int m_KeyCode;
};

// Evento de tecla presionada
class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, bool isRepeat = false)
        : KeyEvent(keycode), m_IsRepeat(isRepeat) {
    }
    
    bool IsRepeat() const { return m_IsRepeat; }
    
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
        return ss.str();
    }
    
    static EventType GetStaticType() { return EventType::KeyPressed; }
    EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "KeyPressed"; }
    
private:
    bool m_IsRepeat;
};

// Evento de tecla liberada
class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keycode)
        : KeyEvent(keycode) {
    }
    
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }
    
    static EventType GetStaticType() { return EventType::KeyReleased; }
    EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "KeyReleased"; }
};

// Evento de tecla escrita (para entrada de texto)
class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(int keycode)
        : KeyEvent(keycode) {
    }
    
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_KeyCode;
        return ss.str();
    }
    
    static EventType GetStaticType() { return EventType::KeyTyped; }
    EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "KeyTyped"; }
};

} // namespace Destiny