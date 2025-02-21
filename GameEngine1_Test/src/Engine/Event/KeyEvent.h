#if !defined(KEYEVENT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Event.h"

namespace Engine
{

    class ENGINE_API KeyEvent : public Event
    {
    public:
        inline i32 GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

    protected:
        keyEvent(i32 keycode)
                : m_KeyCode(keycode) {}

        i32 m_KeyCode;

    };

    class ENGINE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(i32 keycode, i32 repeatCount)
                : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline i32 GetRepeatCount() { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
        
    private:
        i32 m_RepeatCount;

    };

}

#define KEYEVENT_H
#endif
