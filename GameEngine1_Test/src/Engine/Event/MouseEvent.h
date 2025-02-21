#if !defined(MOUSEEVENT_H)
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
    class ENGINE_API MouseMovedEvent : public Event
    {
    public:

         MouseMovedEvent(r32 x, r32 y)
                : mouseX(x), mouseY(y) {}

        inline r32 GetX() const { return mouseX; }
        inline r32 GetY() const { return mouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        
    private:
        r32 mouseX, mouseY;
    };

    class ENGINE_API MouseScrolledEvent : public Event
    {
    public:

         MouseScrolledEvent(r32 x, r32 y)
                : offsetX(x), offsetY(y) {}

        inline r32 GetOffsetX() const { return offsetX; }
        inline r32 GetOffsetY() const { return offsetY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << offsetX << ", " << offsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrooled);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        
    private:
        r32 offsetX, offsetY;
    };


    class ENGINE_API MouseButtonEvent : public Event
    {
    public:
        inline i32 GetButton() const { return button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        
    private:
        MouseButtonEvent(i32 button)
            : button(button) {}
        i32 button;
    };

    
    class ENGINE_API MousePressedEvent : public MouseButtonEvent
    {
    public:
        MousePressedEvent(i32 button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
        
    };

    
    class ENGINE_API MouseReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseReleasedEvent(i32 button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseReleasedEvent: " << button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);

    };
        

}

#define MOUSEEVENT_H
#endif
