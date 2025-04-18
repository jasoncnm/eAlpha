/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "OpenGLErrorHandler.h"
#include <glad/glad.h>

namespace Engine
{

    OpenGLTexture2D::OpenGLTexture2D(const std::string & path)
            : path(path)
    {
        int x,y, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char * data = stbi_load(path.c_str(), &x, &y, &channels, 0);
        ENGINE_CORE_ASSERT(data, "Failed to load image!");

        width = x;
        height = y;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        ENGINE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
        
        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
        u32 error = glGetError();
        if (error)
        {
            ENGINE_CORE_ERROR("ERROR: Fail to create Texture with code: {0}", glCheckError(error));
            ENGINE_CORE_ASSERT(false, "Fail to create Texture");
        }
        glTextureStorage2D(rendererID, 1, internalFormat, width, height);
        glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(rendererID,
                            0,
                            0,
                            0,
                            width,
                            height,
                            dataFormat,
                            GL_UNSIGNED_BYTE,
                            data);
        error = glGetError();
        if (error)
        {
            ENGINE_CORE_ERROR("ERROR: Fail to specify texture subimage with code: {0}", glCheckError(error));
            ENGINE_CORE_ASSERT(false, "Fail to specify texture subimage");
        }

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &rendererID);
    }

    void OpenGLTexture2D::Bind(u32 slot) const
    {
        glBindTextureUnit(slot, rendererID);
        u32 error = glGetError();
        if (error)
        {
            ENGINE_CORE_ERROR("ERROR: Fail to bind texture with code: {0}", glCheckError(error));
            ENGINE_CORE_ASSERT(false, "Fail to bind texture");
        }
    }

}
