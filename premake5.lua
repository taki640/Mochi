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

include "Mochi/Build-Mochi.lua"
include "MochiSandbox/Build-MochiSandbox.lua"
