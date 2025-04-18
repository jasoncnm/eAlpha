/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
 

#include <Engine.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ExtractShaderSourceCode(const std::string & filePath)
{
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    
    std::ifstream file(filePath);
    std::stringstream ss[2];

    std::string line;
    ShaderType type = ShaderType::NONE;

    while (getline(file, line)) {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
        
    }
    ShaderProgramSource source = { ss[0].str(), ss[1].str() };
    return source;
}


class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
            : Layer("Example"), camera(-1.6f, 1.6f, -.9f, .9f), cameraPos(0.0f), squarePos(0.0f)
    {        
        // --------------------------------------------------
        // Triangle
        // --------------------------------------------------
        
        // Vertex Array & Vertex Buffer
        triangleVA.reset(Engine::VertexArray::Create());
        
        r32 vertices[3 * 7] =
            {
                .0f,  .5f,  .0f,  1.0f,  .0f,  .0f, 1.0f,
                -.5f, -.5f,  .0f,   .0f, 1.0f,  .0f, 1.0f,
                .5f, -.5f,  .0f,   .0f,  .0f, 1.0f, 1.0f
            };

        Engine::Ref<Engine::VertexBuffer> triangleVB;
        Engine::Ref<Engine::IndexBuffer> triangleIB;                
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
        
        blueSquareVA.reset(Engine::VertexArray::Create());        

        r32 squareVertices[4 * 5] =
            {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
            };
        Engine::Ref<Engine::VertexBuffer> blueSquareVB;
        Engine::Ref<Engine::IndexBuffer> blueSquareIB;

        blueSquareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Engine::BufferLayout blueSquareLayout = { { Engine::ShaderDataType::Float3, "position" },
                                                  { Engine::ShaderDataType::Float2, "texCoord" } };
                                                  
        blueSquareVB->SetLayout(blueSquareLayout);
        blueSquareVA->AddVertexBuffer(blueSquareVB);

        u32 blueSquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        blueSquareIB.reset(Engine::IndexBuffer::Create(blueSquareIndices, 6));
        blueSquareVA->SetIndexBuffer(blueSquareIB);

                
        // Shader
        ShaderProgramSource source = ExtractShaderSourceCode("src/Assets/Triangle.shader");        
        ENGINE_INFO("TriangleVS: {0}", source.VertexSource);
        ENGINE_INFO("TriangleFS: {0}", source.FragmentSource);
        triangleShader.reset(Engine::Shader::Create(source.VertexSource, source.FragmentSource));

        source = ExtractShaderSourceCode("src/Assets/FlatColor.shader");
        ENGINE_INFO("BlueSquareVS: {0}", source.VertexSource);
        ENGINE_INFO("BlueSquareFS: {0}", source.FragmentSource);
        blueSquareShader.reset(Engine::Shader::Create(source.VertexSource, source.FragmentSource));

        
        source = ExtractShaderSourceCode("src/Assets/Texture.shader");
        ENGINE_INFO("TextureVS: {0}", source.VertexSource);
        ENGINE_INFO("TextureFS: {0}", source.FragmentSource);
        textureShader.reset(Engine::Shader::Create(source.VertexSource, source.FragmentSource));

        texture = Engine::Texture2D::Create("src/Assets/Textures/test.png");

        logoTexture = Engine::Texture2D::Create("src/Assets/Textures/test2.png");

        std::dynamic_pointer_cast<Engine::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(textureShader)->UploadUniformInt("_Texture", 0);

    }

    void OnUpdate(Engine::TimeStep timeStep) override
    {

        // ENGINE_TRACE("Delta Time: {0}s ({1}ms)", timeStep.GetSeconds(), timeStep.GetMilliSeconds());
        
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

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Engine::OpenGLShader>(blueSquareShader)->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(blueSquareShader)->UploadUniformFloat3("Color", squareColor);
        for (u32 x = 0; x < 10; x++)
        {
            for (u32 y = 0; y < 10; y++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0);
                glm::mat4 transform = glm::translate(glm::mat4(1.0), pos) * scale;
                Engine::Renderer::Submit(blueSquareShader, blueSquareVA, transform);
            } 
        }

        texture->Bind();
        Engine::Renderer::Submit(textureShader, blueSquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));
        logoTexture->Bind();
        Engine::Renderer::Submit(textureShader, blueSquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));
        //Engine::Renderer::Submit(triangleShader, triangleVA);

        Engine::Renderer::EndScene();

    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
        ImGui::End();
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
    
    Engine::Ref<Engine::VertexArray> triangleVA;
    Engine::Ref<Engine::VertexArray> blueSquareVA;


    Engine::Ref<Engine::Shader> triangleShader;
    Engine::Ref<Engine::Shader> blueSquareShader;        
    Engine::Ref<Engine::Shader> textureShader;        

    Engine::Ref<Engine::Texture2D> texture, logoTexture;
    
    Engine::OrthographicCamera camera;

    glm::vec3 cameraPos;

    glm::vec3 squarePos;
    glm::vec3 squareColor = glm::vec3(0.2f, 0.2f, 0.7f);

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
