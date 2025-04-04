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

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> & vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> & indexBuffer) override;
                
        virtual const std::vector<std::shared_ptr<VertexBuffer>> & GetVertexBuffers() const override { return vertexBuffers; }
        virtual const std::shared_ptr<IndexBuffer> & GetIndexBuffer() const override { return indexBuffer; }

    private:

        u32 rendererId;
        
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
    
}

#define OPENGLVERTEXARRAY_H
#endif
