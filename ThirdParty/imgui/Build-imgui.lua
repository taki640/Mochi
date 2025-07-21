-- Build-imgui.lua

project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir (MOCHI_TARGET_DIR_FORMAT)
    objdir (MOCHI_OBJ_DIR_FORMAT)

    files {
        "imgui/imconfig.h",
        "imgui/imgui.h",
        "imgui/imgui.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_internal.h",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/imstb_rectpack.h",
        "imgui/imstb_textedit.h",
        "imgui/imstb_truetype.h",
        "imgui/imgui_demo.cpp",
        "imgui/misc/cpp/imgui_stdlib.cpp",
        "imgui/misc/cpp/imgui_stdlib.h",
        "imgui/backends/imgui_impl_opengl3.cpp",
        "imgui/backends/imgui_impl_opengl3.h",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_glfw.h"
    }

    includedirs {
        "imgui",
        "../glfw/glfw/include"
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        pic "On"
        systemversion "latest"

    filter (DEBUG_FILTER)
        runtime "Debug"
        symbols "On"
    filter (RELEASE_FILTER)
        runtime "Release"
        symbols "On"
        optimize "On"
    filter (FINAL_FILTER)
        runtime "Release"
        symbols "Off"
        optimize "On"
