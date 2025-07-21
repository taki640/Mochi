MOCHI_TARGET_DIR_FORMAT   = "%{wks.location}/Bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
MOCHI_OBJ_DIR_FORMAT      = "%{wks.location}/Bin/Int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
MOCHI_DEBUG_FILTER        = "configurations:Debug"
MOCHI_RELEASE_FILTER      = "configurations:Release"
MOCHI_FINAL_FILTER        = "configurations:Final"

-- Filters for third-party libraries
DEBUG_FILTER    = MOCHI_DEBUG_FILTER
RELEASE_FILTER  = MOCHI_RELEASE_FILTER
FINAL_FILTER    = MOCHI_FINAL_FILTER

IMGUI_USE_USER_H = true
IMGUI_USE_IMGUI_USER_STD_STRING = true

function MochiApplicationWorkspace(mochiPath, wksName, startProjectName, clientPremakeProjects)
    workspace (wksName)
        architecture "x64"
        startproject (startProjectName)
        flags "MultiprocessorCompile"
        configurations {
            "Debug",
            "Release",
            "Final"
        }

        filter "system:windows"
            defines "MOCHI_WINDOWS"

        filter (MOCHI_DEBUG_FILTER)
            defines "MOCHI_DEBUG"
        filter (MOCHI_RELEASE_FILTER)
            defines { "MOCHI_RELEASE", "NDEBUG" }
        filter (MOCHI_FINAL_FILTER)
            defines { "MOCHI_FINAL", "NDEBUG" }

    group "ThirdParty"
        include (mochiPath .. "/ThirdParty/imgui/Build-imgui.lua")
        include (mochiPath .. "/ThirdParty/glfw/Build-glfw.lua")
    group ""

    include (mochiPath .. "/Mochi/Build-Mochi.lua")

    if type(clientPremakeProjects) ~= "table" then
        clientPremakeProjects = { clientPremakeProjects }
    end

    for _, v in ipairs(clientPremakeProjects) do
        nameAndGroup = {}
        if type(v) ~= "table" then
            nameAndGroup[1] = v
            nameAndGroup[2] = ""
        else
            nameAndGroup[1] = v[1]
            nameAndGroup[2] = v[2]
        end

        group (nameAndGroup[2])
            include (nameAndGroup[1])
        group ""
    end
end
