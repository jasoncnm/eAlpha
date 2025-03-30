workspace "eAlpha"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "SandBox"

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["spdlog"] = "eAlpha/vendor/spdlog/include"
IncludeDir["GLFW"] = "eAlpha/vendor/GLFW/include"
IncludeDir["Glad"] = "eAlpha/vendor/Glad/include"
IncludeDir["Imgui"] = "eAlpha/vendor/Imgui"
IncludeDir["glm"] = "eAlpha/vendor/glm"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"


group "Dependencies"
     include "eAlpha/vendor/GLFW"
     include "eAlpha/vendor/Glad"
     include "eAlpha/vendor/Imgui"
group ""

project "eAlpha"
    location "eAlpha"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "eAlpha/src/pch.cpp"

    files { "%{prj.name}/src/**.h",
	        "%{prj.name}/src/**.cpp",
            "%{prj.name}/vendor/glm/glm/**.hpp",
            "%{prj.name}/vendor/glm/glm/**.inl", }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.VulkanSDK}",
    }

    links
    {
        "GLFW",
        "Glad",
        "Imgui",
        "%{Library.Vulkan}",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS",  "ENGINE_BUILD_DLL", "GLFW_INCLUDE_NONE", "ENGINE_API_OPENGL" }

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
    cppdialect "C++17"

    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
    {
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.VulkanSDK}",
	    "eAlpha/src",
	    "eAlpha/vendor",
    }

    links
    {
        "eAlpha"
    }

    filter "system:windows"
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
