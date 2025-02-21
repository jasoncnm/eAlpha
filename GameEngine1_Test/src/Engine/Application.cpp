/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{

    Application::Application()
    {
    }


    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        ENGINE_TRACE(e);
        while(true);
    }

}
