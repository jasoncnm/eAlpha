workspace "eAlpha"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "SandBox"

IncludeDir = {}
IncludeDir["GLFW"] = "eAlpha/vendor/GLFW/include"
IncludeDir["Glad"] = "eAlpha/vendor/Glad/include"
IncludeDir["Imgui"] = "eAlpha/vendor/Imgui"

include "eAlpha/vendor/GLFW"
include "eAlpha/vendor/Glad"
include "eAlpha/vendor/Imgui"


project "eAlpha"
    location "eAlpha"
    kind "SharedLib"
    language "C++"

    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "eAlpha/src/pch.cpp"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
    }

    links
    {
        "GLFW",
        "Glad",
        "Imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS",  "ENGINE_BUILD_DLL", "GLFW_INCLUDE_NONE" }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
        }

        buildoptions "/utf-8 "

    filter "configurations:Debug"
        defines { "ENGINE_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "ENGINE_DIST" }
	runtime "Release"
        optimize "On"

 
project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    staticruntime "off"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
    {
        "eAlpha/vendor/spdlog/include",
        "eAlpha/src"
    }

    links
    {
        "eAlpha"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS" }

        buildoptions "/utf-8 "

    filter "configurations:Debug"
        defines { "ENGINE_DEBUG"  }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "ENGINE_DIST" }
        runtime "Release"
        optimize "On"
