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
        static void Init();
        static void BeginScene(OrthographicCamera & camera);
        static void EndScene();
        static void Submit(Ref<Shader> shader, const Ref<VertexArray> & vertexArray,
                           const glm::mat4 & transform = glm::mat4(1.0f));
        
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
