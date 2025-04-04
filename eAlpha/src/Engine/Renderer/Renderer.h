#if !defined(RENDERER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Engine
{

    class Renderer
    {
    public:

        static void BeginScene(OrthographicCamera & camera);
        static void EndScene();
        static void Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> & vertexArray);
        
        inline static RendererAPI::API  GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 viewProj;
        };

        static SceneData * sceneData;
    };
}

#define RENDERER_H
#endif
