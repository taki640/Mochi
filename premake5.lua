-- premake5.lua
workspace "Mochi"
   architecture "x64"
   startproject "MochiSandbox"
   configurations {
      "Debug",
      "Release",
      "Final"
   }

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "ThirdParty"
   DEBUG_FILTER = "configurations:Debug"
   RELEASE_FILTER = "configurations:Release or Final"

   include "ThirdParty/imgui/Build-imgui.lua"
   include "ThirdParty/glfw/Build-glfw.lua"
group ""

include "Mochi/Build-Mochi.lua"
include "MochiSandbox/Build-MochiSandbox.lua"
