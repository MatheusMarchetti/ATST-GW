workspace "ATST-GW"
    architecture "x64"
    systemversion "latest"
    language "C++"
    cppdialect "C++17"
    characterset("Unicode")

    configurations
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}"

project "ATST-GW"
    kind "ConsoleApp"
    staticruntime "On"
    location("ATST-GW")

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "corepch.h"
    pchsource "ATST-GW/src/corepch.cpp"

    IncludeDir = {}
    IncludeDir["glm"] = "ATST-GW/vendor/glm"

    links
    {
        
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.glm}"
    }

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
        optimize "On"