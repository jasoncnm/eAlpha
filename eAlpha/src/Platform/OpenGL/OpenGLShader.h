#if !defined(OPENGLSHADER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/Shader.h"

namespace Engine
{

    class OpenGLShader : public Shader
    {
    public:

        OpenGLShader(std::string vertexSource, std::string fragmentSource);

        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual u32 GetAttribLocation(const char * attribName);

    private:
        u32 rendererId;
        
    };
    
}


#define OPENGLSHADER_H
#endif
