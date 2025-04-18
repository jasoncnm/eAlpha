#if !defined(TEXTURE_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <string>
#include "Engine/Core.h"

namespace Engine
{

    class Texture
    {
    public:

        virtual ~Texture() = default;
        
        virtual u32 GetWidth() const = 0;
        virtual u32 GetHeight() const = 0;

        virtual void Bind(u32 slot = 0) const  = 0;
        
    private:

    };

    class Texture2D :public Texture
    {
    public:

        static Ref<Texture2D> Create(const std::string & path);

    };
    
}

#define TEXTURE_H
#endif
