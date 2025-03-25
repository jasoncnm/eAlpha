/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Engine
{

    Shader * Shader::Create(std::string vertexSource, std::string fragmentSource)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:
            {
                ENGINE_CORE_ASSERT(false, "RendererAPI::None is not supported");
                return nullptr;
            }
            case RendererAPI::OpenGL:
            {
                return new OpenGLShader(vertexSource, fragmentSource);
            }
        }
        ENGINE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }

    
}
