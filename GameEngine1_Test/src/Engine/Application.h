#if !defined(APPLICATION_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Core.h"

namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        
    };

    Application CreateApplication();
}

#define APPLICATION_H
#endif
