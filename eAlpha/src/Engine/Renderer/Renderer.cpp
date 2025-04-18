/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{

    Renderer::SceneData * Renderer::sceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        RenderCommand::Init();
    }
        
    void Renderer::BeginScene(OrthographicCamera & camera)
    {
        sceneData->viewProj = camera.GetVPMatrix();
    }
    
    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(Ref<Shader> shader, const Ref<VertexArray> & vertexArray,
                          const glm::mat4 & transform)
    {
        shader->Bind();

        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("VP", sceneData->viewProj);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("Trans", transform);
        
        vertexArray->Bind();
        RenderCommand::DrawIndex(vertexArray);
    }

}
