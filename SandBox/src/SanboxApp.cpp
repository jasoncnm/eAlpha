/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <Engine.h>

class SandBox : public Engine::Application
{
public:
    SandBox(){}
    ~SandBox(){}
};


Engine::Application Engine::CreateApplication()
{
    SandBox sandBox;
    return sandBox;
}
