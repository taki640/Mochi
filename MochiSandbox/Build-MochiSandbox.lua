-- Build-MochiSandbox.lua
project "MochiSandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir (MOCHI_TARGET_DIR_FORMAT)
    objdir (MOCHI_OBJ_DIR_FORMAT)

    files {
        "Build-MochiSandbox.lua",
        "Source/**.h",
        "Source/**.hpp",
        "Source/**.cpp"
    }

    includedirs {
        "Source",
        "%{wks.location}/Mochi/Include",
        "%{wks.location}/ThirdParty/imgui"
    }

    links {
        "Mochi"
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
        kind "WindowedApp"
        runtime "Release"
        optimize "On"
        symbols "Off"
