/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <Engine.h>

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
    }

    void OnEvent(Engine::Event & event) override
    {
        ENGINE_TRACE("{0}", event);
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
