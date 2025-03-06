/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Engine/Log.h"
#include "Application.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{

    Application * Application::instance = nullptr;
    
    Application::Application()
    {
        ENGINE_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;
        
        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    void Application::PushLayer(Layer * layer)
    {
        layerStack.PushLayer(layer);
    }
    
    void Application::PushOverlay(Layer * overlay)
    {
        layerStack.PushOverlay(overlay);
    }

    void Application::OnEvent(Event & event)
    {

        EventDispatcher dispatcher(event);
        std::function<bool(WindowCloseEvent&)> func = BIND_EVENT_FUNCTION(Application::OnWindowClose);
        dispatcher.Dispatch<WindowCloseEvent>(func);
        
        // ENGINE_CORE_TRACE("{0}", event);

        for (auto it = layerStack.end(); it != layerStack.begin(); )
        {
            (*--it)->OnEvent(event);

            if (event.Handled()) break;
        }
        
    }

    bool Application::OnWindowClose(WindowCloseEvent & event)
    {
        Running = false;
        return true;
    }

    Application::~Application()
    {
    }

    
    void Application::Run()
    {
        while(Running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer * layer : layerStack)
            {
                layer->OnUpdate();
            }
            
            window->OnUpdate();
        }
    }

}
