-- Build-MochiSandbox.lua
project "MochiSandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir ("%{wks.location}/Bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Bin/Int/" .. OutputDir .. "/%{prj.name}")

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
        defines { "MOCHI_WINDOWS" }

    filter "configurations:Debug"
        defines { "MOCHI_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "MOCHI_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Final"
        kind "WindowedApp"
        defines { "MOCHI_FINAL" }
        runtime "Release"
        optimize "On"
        symbols "Off"
