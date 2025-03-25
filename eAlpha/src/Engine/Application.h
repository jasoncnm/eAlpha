#if !defined(APPLICATION_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event & event);
        void PushLayer(Layer * layer);
        void PushOverlay(Layer * overlay);

        void ExtractShaderSourceCode(std::string & shaderSource, const std::string & filePath);

        inline static Application& Get() { return *instance; }
        inline Window & GetWindow() { return *window; }
        
    private:
    
        bool OnWindowClose(WindowCloseEvent& event);
        std::unique_ptr<Window> window;
        ImGuiLayer * imGuiLayer;
        bool Running = true;
        LayerStack layerStack;

        u32 vertexArray;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexBuffer> vertexBuffer[2];
        std::unique_ptr<IndexBuffer> indexBuffer;
        
        static Application * instance;
    
    };
    Application * CreateApplication();
}

#define APPLICATION_H
#endif
