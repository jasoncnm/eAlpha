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
#include "Renderer/Renderer.h"

#include <glm/glm.hpp>

namespace Engine
{

    Application * Application::instance = nullptr;

    void Application::ExtractShaderSourceCode(std::string & shaderSource, const std::string & filePath)
    {
        std::ifstream file;

        file.open(filePath.c_str());

        if (!file)
        {
            char buffer[1024];
            
            if (_getcwd(buffer, 1024) != NULL)
            {        
                std::cout << "Current Directory: " << buffer << std::endl;
            }

            ENGINE_CORE_ERROR("filepath: {0}", filePath);
            ENGINE_CORE_ASSERT(false, "Failed to open file");
        }
        std::stringstream strBuffer;
        std::string str;

        while(file.good()) {
            getline(file, str, '\r');
            strBuffer << str;
        }
        file.close();

        strBuffer << '\0';  // Append null terminator.

        shaderSource = strBuffer.str();
    }
    
    Application::Application()
    {
        ENGINE_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;
        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        imGuiLayer = new ImGuiLayer();
        layerStack.PushOverlay(imGuiLayer);

        // --------------------------------------------------
        // Triangle
        // --------------------------------------------------
        
        // Shader
        std::string vertexSrc, fragmentSrc;
        ExtractShaderSourceCode(vertexSrc, "../eAlpha/src/Platform/OpenGL/Assets/Triangle.vs");
        ExtractShaderSourceCode(fragmentSrc, "../eAlpha/src/Platform/OpenGL/Assets/Triangle.fs");
        triangleShader.reset(Shader::Create(vertexSrc, fragmentSrc));

        
        // Vertex Array & Vertex Buffer

        triangleVA.reset(VertexArray::Create());
        
        r32 vertices[3 * 7] =
            {
                .0f,  .5f,  .0f,  1.0f,  .0f,  .0f, 1.0f,
                -.5f, -.5f,  .0f,   .0f, 1.0f,  .0f, 1.0f,
                .5f, -.5f,  .0f,   .0f,  .0f, 1.0f, 1.0f
            };

        std::shared_ptr<VertexBuffer> triangleVB;
        std::shared_ptr<IndexBuffer> triangleIB;                
        triangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout triangleLayout =
            {
                { ShaderDataType::Float3, "position" },
                { ShaderDataType::Float4, "color" }
            };
        triangleVB->SetLayout(triangleLayout);

        triangleVA->AddVertexBuffer(triangleVB);

        // Index Buffer
        u32 indices[3] = { 0, 1, 2 };
        triangleIB.reset(IndexBuffer::Create(indices, 3));
        triangleVA->SetIndexBuffer(triangleIB);

        // --------------------------------------------------
        // Square
        // --------------------------------------------------
        std::string blueSquareVS, blueSquareFS;
        ExtractShaderSourceCode(blueSquareVS, "../eAlpha/src/Platform/OpenGL/Assets/BlueSquare.vs");
        ExtractShaderSourceCode(blueSquareFS, "../eAlpha/src/Platform/OpenGL/Assets/BlueSquare.fs");
        blueSquareShader.reset(Shader::Create(blueSquareVS, blueSquareFS));

        blueSquareVA.reset(VertexArray::Create());        

        r32 squareVertices[4 * 3] =
            {
                -0.75f, -0.75f, 0.0f,
                 0.75f, -0.75f, 0.0f,
                 0.75f, 0.75f, 0.0f,
                -0.75f, 0.75f, 0.0f
            };
        std::shared_ptr<VertexBuffer> blueSquareVB;
        std::shared_ptr<IndexBuffer> blueSquareIB;

        blueSquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        BufferLayout blueSquareLayout = { { ShaderDataType::Float3, "position" }};
        blueSquareVB->SetLayout(blueSquareLayout);
        blueSquareVA->AddVertexBuffer(blueSquareVB);

        u32 blueSquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        blueSquareIB.reset(IndexBuffer::Create(blueSquareIndices, 6));
        blueSquareVA->SetIndexBuffer(blueSquareIB);
        
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

            RenderCommand::SetClearColor({.1f, .1f, .1f, 1});
            RenderCommand::Clear();

            Renderer::BeginScene();

            blueSquareShader->Bind();
            Renderer::Submit(blueSquareVA);

            triangleShader->Bind();
            Renderer::Submit(triangleVA);

            Renderer::EndScene();
            
            for (Layer * layer : layerStack)
            {
                layer->OnUpdate();
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
