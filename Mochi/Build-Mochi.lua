-- Build-Mochi.lua
project "Mochi"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir ("%{wks.location}/Bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Bin/Int/" .. OutputDir .. "/%{prj.name}")

    files {
        "Build-Mochi.lua",
        "Source/**.h",
        "Source/**.hpp",
        "Source/**.cpp",
        "Include/**.h",
        "Include/**.hpp"
    }

    includedirs {
       "Include/Mochi",
       "../ThirdParty/imgui",
       "../ThirdParty/glfw/include"
    }

    links {
        "ImGui",
        "GLFW",
        "Opengl32"
    }

    filter "system:windows"
        systemversion "latest"
        defines "MOCHI_WINDOWS"

    filter "configurations:Debug"
        defines "MOCHI_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "MOCHI_RELEASE"
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Final"
        defines "MOCHI_FINAL"
        runtime "Release"
        optimize "On"
        symbols "Off"
