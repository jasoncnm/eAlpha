#if !defined(OPENGLTEXTURE_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/Texture.h"

namespace Engine
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string & path);
        virtual ~OpenGLTexture2D();
                
        virtual u32 GetWidth() const override { return width; }
        virtual u32 GetHeight() const override { return height; }
        virtual void Bind(u32 slot = 0) const  override;

    private:
        std::string path;

        u32 width;
        u32 height;
        u32 rendererID;
    };
}

#define OPENGLTEXTURE_H
#endif
