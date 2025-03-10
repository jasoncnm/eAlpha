#if !defined(APPLICATION_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"

namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event & event);
        void PushLayer(Layer * layer);
        void PushOverlay(Layer * overlay);

        inline static Application& Get() { return *instance; }
        inline Window & GetWindow() { return *window; }
        
    private:
    
        bool OnWindowClose(WindowCloseEvent& event);
        std::unique_ptr<Window> window;
        ImGuiLayer * imGuiLayer;
        bool Running = true;
        LayerStack layerStack;

        static Application * instance;
    
    };
    Application * CreateApplication();
}

#define APPLICATION_H
#endif
