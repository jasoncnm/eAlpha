/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Renderer.h"

namespace Engine
{

    Renderer::SceneData * Renderer::sceneData = new Renderer::SceneData;
    
    void Renderer::BeginScene(OrthographicCamera & camera)
    {
        sceneData->viewProj = camera.GetVPMatrix();
    }
    
    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> & vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("VP", sceneData->viewProj);
        
        vertexArray->Bind();
        RenderCommand::DrawIndex(vertexArray);
    }

}
