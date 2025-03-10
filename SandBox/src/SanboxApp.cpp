/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */


#include <Engine.h>
#include "imgui/imgui.h"

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
            : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        // ENGINE_INFO("ExampleLayer::Update");
        if (Engine::Input::IsKeyPressed(E_KEY_TAB))
        {
            ENGINE_TRACE("Tab key is pressed");
        }
    }

    void OnEvent(Engine::Event & event) override
    {
        //ENGINE_TRACE("{0}", event);
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }
    
};

class SandBox : public Engine::Application
{
public:
    SandBox()
    {
        PushLayer(new ExampleLayer());
    }
    ~SandBox(){}
}; 


Engine::Application * Engine::CreateApplication()
{
    return new SandBox();
}
