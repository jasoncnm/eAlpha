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
                
        // Shader
        std::string vertexSrc, fragmentSrc;
        ExtractShaderSourceCode(vertexSrc, "../eAlpha/src/Engine/Renderer/Assets/OpenGL.vs");
        ExtractShaderSourceCode(fragmentSrc, "../eAlpha/src/Engine/Renderer/Assets/OpenGL.fs");
        shader.reset(Shader::Create(vertexSrc, fragmentSrc));

        
        // Vertex Array & Vertex Buffer
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        r32 vertices[3 * 3] =
            {
                .0f,  .5f,  .0f,
                -.5f, -.5f,  .0f,
                .5f, -.5f,  .0f, 
            };
        vertexBuffer[0].reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        
        u32 attribLocation = shader->GetAttribLocation("position");
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        r32 colors[3 * 3] =         
            {
                1.0f,  .0f,  .0f,
                .0f, 1.0f,  .0f,
                .0f,  .0f, 1.0f
            };
        vertexBuffer[1].reset(VertexBuffer::Create(colors, sizeof(colors)));
        attribLocation = shader->GetAttribLocation("color");
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        
        // Index Buffer
        u32 indices[3] = { 0, 1, 2 };
        indexBuffer.reset(IndexBuffer::Create(indices, 3));        
        // indexBuffer.Bind();
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
            glClearColor(.1f, .1f, .1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->Bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
            
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
