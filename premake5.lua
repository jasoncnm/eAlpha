workspace "GameEngine1_Test"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GameEngine1_Test"
    location "GameEngine1_Test"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "GameEngine1_Test/src/pch.cpp"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS",  "ENGINE_BUILD_DLL" }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
        }

        buildoptions "/utf-8 "

    filter "configurations:Debug"
        defines { "ENGINE_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "ENGINE_DIST" }
        optimize "On"

 
project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
    {
        "GameEngine1_Test/vendor/spdlog/include",
        "GameEngine1_Test/src"
    }

    links
    {
        "GameEngine1_Test"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS" }

        buildoptions "/utf-8 "

    filter "configurations:Debug"
        defines { "ENGINE_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "ENGINE_DIST" }
        optimize "On"