#if !defined(VERTEXARRAY_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Buffer.h"

namespace Engine
{

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> & vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> & indexBuffer) = 0;
        
        virtual const std::vector<Ref<VertexBuffer>> & GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer> & GetIndexBuffer() const = 0;

        static VertexArray * Create();        

    };

}

#define VERTEXARRAY_H
#endif
