#if !defined(OPENGLERRORHANDLER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <string>

namespace Engine
{
    std::string glCheckError(u32 errorCode)
    {
        std::string error;
        switch (errorCode)
        {
            case 1280:                        error = "INVALID_ENUM"; break;
            case 1281:                       error = "INVALID_VALUE"; break;
            case 1282:                   error = "INVALID_OPERATION"; break;
            case 1283:                      error = "STACK_OVERFLOW"; break;
            case 1284:                     error = "STACK_UNDERFLOW"; break;
            case 1285:                       error = "OUT_OF_MEMORY"; break;
            case 1286:       error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        return error;
    }
}
#define OPENGLERRORHANDLER_H
#endif
