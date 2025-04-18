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
#include "KeyCode.h"
#include "TimeStep.h"
#include "Renderer/Renderer.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{

    Application * Application::instance = nullptr;
    
    Application::Application()
    {
        ENGINE_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;
        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        window->SetVSync(false);

        Renderer::Init();
        
        imGuiLayer = new ImGuiLayer();
        layerStack.PushOverlay(imGuiLayer);

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


#include <iostream>

    void Application::Run()
    {
        while(Running)
        {

            r32 time = (r32)glfwGetTime();
            TimeStep timeStep = time - lastFrameTime;
            lastFrameTime = time;
            
            for (Layer * layer : layerStack)
            {
                layer->OnUpdate(timeStep);
            }

            imGuiLayer->Begin();
            for (Layer * layer : layerStack)
            {
                layer->OnImGuiRender();
            }
            imGuiLayer->End();

            window->OnUpdate();
            
        }
    }

}
