/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine
{

    Ref<Texture2D> Texture2D::Create(const std::string & path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                ENGINE_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return std::make_shared<OpenGLTexture2D>(path);
            }
        }
        ENGINE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
 
}
