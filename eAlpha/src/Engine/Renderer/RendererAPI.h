#if !defined(RENDERERAPI_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "VertexArray.h"
#include <glm/glm.hpp>

namespace Engine
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1,
            D3D11 = 2,
            D3D12 = 3
        };

        virtual void SetClearColor(const glm::vec4 & color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndex(const std::shared_ptr<VertexArray> & vertexArray) = 0;

        inline static API GetAPI() { return api; }
    private:
        static API api;
    };
}

#define RENDERERAPI_H
#endif
