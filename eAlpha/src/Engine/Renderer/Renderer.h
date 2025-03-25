#if !defined(RENDERER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

namespace Engine
{
    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1,
        D3D11 = 2,
        D3D12 = 3
    };

    class Renderer
    {
    public:

        inline static RendererAPI GetAPI() { return rendererAPI; }
        
    private:
        
        static RendererAPI rendererAPI;
    };
}

#define RENDERER_H
#endif
