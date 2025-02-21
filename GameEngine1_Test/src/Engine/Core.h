#if !defined(CORE_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#ifdef ENGINE_PLATFORM_WINDOWS
#ifdef ENGINE_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else 
#define ENGINE_API __declspec(dllimport)
#endif
#else
#error Engine Only Support Windows!
#endif

#include "Types.h"
#define BIT(x) (1 << x)


#define CORE_H
#endif
