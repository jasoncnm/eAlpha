#if !defined(OPENGLSHADER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/Shader.h"
#include <glm/glm.hpp>
namespace Engine
{

    class OpenGLShader : public Shader
    {
    public:

        OpenGLShader(std::string vertexSource, std::string fragmentSource);

        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        void UploadUniformInt(const std::string & name, const i32 value);

        void UploadUniformFloat (const std::string & name, const r32       & value);
        void UploadUniformFloat2(const std::string & name, const glm::vec2 & value);
        void UploadUniformFloat3(const std::string & name, const glm::vec3 & value);
        void UploadUniformFloat4(const std::string & name, const glm::vec4 & value);

        void UploadUniformMat3(const std::string & name, const glm::mat3 & matrix);
        void UploadUniformMat4(const std::string & name, const glm::mat4 & matrix);

        u32 GetAttribLocation(const char * attribName);

    private:
        u32 rendererId;
        
    };
    
}


#define OPENGLSHADER_H
#endif
