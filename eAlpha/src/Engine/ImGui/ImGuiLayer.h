#if !defined(IMGUILAYER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Layer.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/ApplicationEvent.h"

enum ImGuiKey;

namespace Engine
{
    class ENGINE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        ImGuiKey GLFWKeyToImGuiKey(int keycode);
        
        void OnAttatch() override;
        void OnDetach() override;

        void OnUpdate() override;
        void OnEvent(Event & event) override;

    private:
        r32 lastTime = 0.0f;

        bool OnMouseButtonPressed(MousePressedEvent & event);
        bool OnMouseButtonReleased(MouseReleasedEvent & event);
        bool OnMouseMoved(MouseMovedEvent & event);
        bool OnMouseScrolled(MouseScrolledEvent & event);
        bool OnKeyPressed(KeyPressedEvent & event);
        bool OnKeyReleased(KeyReleasedEvent & event);
        bool OnKeyTyped(KeyTypedEvent & event);
        bool OnWindowResize(WindowResizeEvent & event);

    };
}
#define IMGUILAYER_H
#endif
