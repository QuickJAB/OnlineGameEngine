workspace "OnlineGame"
    architecture "x86_64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {
    SDL = "extern/SDL/install/include",
    ENet = "extern/enet/install/include",
    stb  = "extern/stb"
}

local function copySDLdll(targetDir)
    postbuildcommands {
        'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
    }
end

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"
    systemversion "latest"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }
    includedirs { "%{IncludeDir.SDL}", "%{IncludeDir.ENet}", "%{IncludeDir.stb}" }
    libdirs { "extern/SDL/install/lib", "extern/enet/install/lib" }
    links { "SDL3", "enet", "ws2_32", "winmm" }

project "Game"
    location "Game"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"
    systemversion "latest"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }
    includedirs { "Engine", "%{IncludeDir.SDL}", "%{IncludeDir.ENet}", "%{IncludeDir.stb}" }
    links { "Engine" }
    dependson { "Engine" }

project "Client"
    location "Client"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"
    systemversion "latest"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }
    includedirs { "Engine", "%{IncludeDir.SDL}", "%{IncludeDir.ENet}", "%{IncludeDir.stb}", "Game" }
    links { "Game" }
    dependson { "Game" }
    postbuildcommands { copySDLdll("%{cfg.targetdir}") }

project "Server"
    location "Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"
    systemversion "latest"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }
    includedirs { "Engine", "%{IncludeDir.SDL}", "%{IncludeDir.ENet}", "%{IncludeDir.stb}", "Game" }
    links { "Game" }
    dependson { "Game" }
    postbuildcommands { copySDLdll("%{cfg.targetdir}") }
