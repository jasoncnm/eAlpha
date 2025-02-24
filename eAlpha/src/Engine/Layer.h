#if !defined(LAYER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Core.h"
#include "Engine/Event/Event.h"

namespace Engine
{

    class ENGINE_API Layer
    {
    public:
        Layer(const std::string & name = "Layer");
        virtual ~Layer();

        virtual void OnAttatch() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event & event) {}

        inline const std::string GetName() { return debugName; }

    private:
        std::string debugName;
    };

}

#define LAYER_H
#endif
