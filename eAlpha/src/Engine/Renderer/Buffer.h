#if !defined(BUFFER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

namespace Engine
{

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        static VertexBuffer * Create(float * vertices, u32 size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual u32 GetCount() const = 0;
        
        static IndexBuffer * Create(u32 * indices, u32 count);        
    };

}

#define BUFFER_H
#endif
