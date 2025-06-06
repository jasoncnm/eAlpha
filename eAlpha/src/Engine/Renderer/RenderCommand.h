#if !defined(RENDERCOMMAND_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "RendererAPI.h"

namespace Engine
{
    class RenderCommand
    {
    public:

        static inline void Init() { rendererAPI->Init(); }
        
        static inline void SetClearColor(const glm::vec4 & color) { rendererAPI->SetClearColor(color); }

        static inline void Clear() { rendererAPI->Clear(); }
        
        inline static void DrawIndex(const Ref<VertexArray> & vertexArray)
        {
            rendererAPI->DrawIndex(vertexArray);
        }
    private:
        static RendererAPI * rendererAPI;
    };
}

#define RENDERCOMMAND_H
#endif
