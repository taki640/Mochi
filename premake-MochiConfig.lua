MOCHI_TARGET_DIR_FORMAT   = "%{wks.location}/Bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
MOCHI_OBJ_DIR_FORMAT      = "%{wks.location}/Bin/Int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
MOCHI_DEBUG_FILTER        = "configurations:Debug"
MOCHI_RELEASE_FILTER      = "configurations:Release"
MOCHI_FINAL_FILTER        = "configurations:Final"

-- Filters for third-party libraries
DEBUG_FILTER    = MOCHI_DEBUG_FILTER
RELEASE_FILTER  = MOCHI_RELEASE_FILTER
FINAL_FILTER    = MOCHI_FINAL_FILTER

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
            defines "MOCHI_RELEASE"
        filter (MOCHI_FINAL_FILTER)
            defines "MOCHI_FINAL"

    group "ThirdParty"
        include (mochiPath .. "/ThirdParty/imgui/Build-imgui.lua")
        include (mochiPath .. "/ThirdParty/glfw/Build-glfw.lua")
    group ""

    include (mochiPath .. "/Mochi/Build-Mochi.lua")

    if type(clientPremakeProjects) ~= "table" then
        clientPremakeProjects = { clientPremakeProjects }
    end

    for _, v in ipairs(clientPremakeProjects) do
        include (v)
    end
end
