#if !defined(OPENGLVERTEXARRAY_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Buffer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();
        
        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> & vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> & indexBuffer) override;
                
        virtual const std::vector<Ref<VertexBuffer>> & GetVertexBuffers() const override { return vertexBuffers; }
        virtual const Ref<IndexBuffer> & GetIndexBuffer() const override { return indexBuffer; }

    private:

        u32 rendererId;
        
        std::vector<Ref<VertexBuffer>> vertexBuffers;
        Ref<IndexBuffer> indexBuffer;
    };
    
}

#define OPENGLVERTEXARRAY_H
#endif
