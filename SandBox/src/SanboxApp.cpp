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
            : Layer("Example"), camera(-1.6f, 1.6f, -.9f, .9f), cameraPos(0.0f)
    {        
        // --------------------------------------------------
        // Triangle
        // --------------------------------------------------
        
        // Shader
        std::string vertexSrc, fragmentSrc;
        Engine::Application::Get().ExtractShaderSourceCode(vertexSrc, "./src/Assets/Triangle.vs");
        Engine::Application::Get().ExtractShaderSourceCode(fragmentSrc, "./src/Assets/Triangle.fs");
        triangleShader.reset(Engine::Shader::Create(vertexSrc, fragmentSrc));

        
        // Vertex Array & Vertex Buffer
        triangleVA.reset(Engine::VertexArray::Create());
        
        r32 vertices[3 * 7] =
            {
                .0f,  .5f,  .0f,  1.0f,  .0f,  .0f, 1.0f,
                -.5f, -.5f,  .0f,   .0f, 1.0f,  .0f, 1.0f,
                .5f, -.5f,  .0f,   .0f,  .0f, 1.0f, 1.0f
            };

        std::shared_ptr<Engine::VertexBuffer> triangleVB;
        std::shared_ptr<Engine::IndexBuffer> triangleIB;                
        triangleVB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

        Engine::BufferLayout triangleLayout =
            {
                { Engine::ShaderDataType::Float3, "position" },
                { Engine::ShaderDataType::Float4, "color" }
            };
        triangleVB->SetLayout(triangleLayout);
        triangleVA->AddVertexBuffer(triangleVB);

        // Index Buffer
        u32 indices[3] = { 0, 1, 2 };
        triangleIB.reset(Engine::IndexBuffer::Create(indices, 3));
        triangleVA->SetIndexBuffer(triangleIB);

        // --------------------------------------------------
        // Square
        // --------------------------------------------------
        std::string blueSquareVS, blueSquareFS;
        Engine::Application::Get().ExtractShaderSourceCode(blueSquareVS, "./src/Assets/BlueSquare.vs");
        Engine::Application::Get().ExtractShaderSourceCode(blueSquareFS, "./src/Assets/BlueSquare.fs");
        blueSquareShader.reset(Engine::Shader::Create(blueSquareVS, blueSquareFS));

        blueSquareVA.reset(Engine::VertexArray::Create());        

        r32 squareVertices[4 * 3] =
            {
                -0.75f, -0.75f, 0.0f,
                0.75f, -0.75f, 0.0f,
                0.75f, 0.75f, 0.0f,
                -0.75f, 0.75f, 0.0f
            };
        std::shared_ptr<Engine::VertexBuffer> blueSquareVB;
        std::shared_ptr<Engine::IndexBuffer> blueSquareIB;

        blueSquareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Engine::BufferLayout blueSquareLayout = { { Engine::ShaderDataType::Float3, "position" }};
        blueSquareVB->SetLayout(blueSquareLayout);
        blueSquareVA->AddVertexBuffer(blueSquareVB);

        u32 blueSquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        blueSquareIB.reset(Engine::IndexBuffer::Create(blueSquareIndices, 6));
        blueSquareVA->SetIndexBuffer(blueSquareIB);
        

    }

    void OnUpdate(Engine::TimeStep timeStep) override
    {

        ENGINE_TRACE("Delta Time: {0}s ({1}ms)", timeStep.GetSeconds(), timeStep.GetMilliSeconds());
        
        Engine::RenderCommand::SetClearColor({.1f, .1f, .1f, 1});
        Engine::RenderCommand::Clear();

        r32 speed = 1.0f;
        
        if (Engine::Input::IsKeyPressed(E_KEY_W))
        {
            cameraPos.y -= speed * timeStep;
        }
        else if (Engine::Input::IsKeyPressed(E_KEY_S))
        {
            cameraPos.y += speed * timeStep;
        }

        if (Engine::Input::IsKeyPressed(E_KEY_A))
        {
            cameraPos.x += speed * timeStep;
        }
        else if (Engine::Input::IsKeyPressed(E_KEY_D))
        {
            cameraPos.x -= speed * timeStep;
        }

        r32 rotSpeed = 30.0f;
        if (Engine::Input::IsKeyPressed(E_KEY_E))
        {
            cameraRot += rotSpeed * timeStep;
        }
        else if (Engine::Input::IsKeyPressed(E_KEY_Q))
        {
            cameraRot -= rotSpeed * timeStep;
        }
        
        camera.SetPosition(cameraPos);
        camera.SetRotation(cameraRot);
        
        Engine::Renderer::BeginScene(camera);
            
        Engine::Renderer::Submit(blueSquareShader, blueSquareVA);
        Engine::Renderer::Submit(triangleShader, triangleVA);

        Engine::Renderer::EndScene();

    }

    void OnImGuiRender() override
    {
    }
    
    void OnEvent(Engine::Event & event) override
    {

    }

    bool OnKeyPressedEvent(Engine::KeyPressedEvent & event)
    {

        if (event.GetKeyCode() == E_KEY_E)
        {
            camera.SetRotation(45.0f);
        }
        
        return false;
    }

    bool OnKeyReleaseEvent(Engine::KeyReleasedEvent & event)
    {

        if (event.GetKeyCode() == E_KEY_E)
        {
            camera.SetRotation(.0f);
        }
        
        return false;
    }    

    bool OnMouseMovedEvent(Engine::MouseMovedEvent & event)
    {

        Engine::Window & window = Engine::Application::Get().GetWindow();
        
        glm::vec3 pos
            {
                (event.GetX() / window.GetWidth() - 0.5f) * -3.2f,
                (event.GetY() / window.GetHeight() - .5f) * 1.8f,
                0.0f
            };

        camera.SetPosition(pos);

        return false;
    }

private:
    
    std::shared_ptr<Engine::VertexArray> triangleVA;
    std::shared_ptr<Engine::Shader> triangleShader;


    std::shared_ptr<Engine::VertexArray> blueSquareVA;
    std::shared_ptr<Engine::Shader> blueSquareShader;        

    Engine::OrthographicCamera camera;

    glm::vec3 cameraPos;

    r32 cameraRot = 0.0f;
    
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
