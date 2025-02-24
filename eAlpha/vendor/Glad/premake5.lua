project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/**.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"