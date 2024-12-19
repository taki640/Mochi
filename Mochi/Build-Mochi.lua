-- Build-Mochi.lua
project "Mochi"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir (MOCHI_TARGET_DIR_FORMAT)
    objdir (MOCHI_OBJ_DIR_FORMAT)

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
       "../ThirdParty/glfw/include",
       "../ThirdParty/stb"
    }

    links {
        "ImGui",
        "GLFW",
        "Opengl32"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Final"
        runtime "Release"
        optimize "On"
        symbols "Off"
