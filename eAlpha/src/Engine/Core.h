#if !defined(CORE_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <memory> 

#ifdef ENGINE_PLATFORM_WINDOWS

#else
#error Engine Only Support Windows!
#endif

#ifdef ENGINE_DEBUG
#define ENGINE_ENABLE_ASSERTS
#endif

#ifdef ENGINE_ENABLE_ASSERTS
#define ENGINE_ASSERT(x, ...) { if (!(x)) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ENGINE_CORE_ASSERT(x, ...) { if (!(x)) { ENGINE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ENGINE_ASSERT(x, ...)
#define ENGINE_CORE_ASSERT(x, ...)
#endif

#include "Types.h"
#define BIT(x) (1 << x)
#define BIND_EVENT_FUNCTION(X) std::bind(&X, this, std::placeholders::_1)

namespace Engine
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
    
}

#define CORE_H
#endif
