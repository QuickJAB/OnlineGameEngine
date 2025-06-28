workspace "OnlineGame"
    architecture "x86_64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL"] = "extern/SDL/install/include"
IncludeDir["ENet"] = "extern/enet/install/include"
IncludeDir["stb"] = "extern/stb"

LibraryDir = {}
LibraryDir["SDL_Debug"] = "extern/SDL/install/lib"
LibraryDir["SDL_Release"] = "extern/SDL/install/lib"
LibraryDir["ENet_Debug"] = "extern/enet/install/lib"
LibraryDir["ENet_Release"] = "extern/enet/install/lib"

DLLDir = "extern/SDL/install/bin"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"            -- Use dynamic CRT (/MD)

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Engine/**.h",
        "Engine/**.cpp"
    }

    includedirs {
        "Engine",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.ENet}",
        "%{IncludeDir.stb}"
    }

    filter "configurations:Debug"
        runtime "Debug"
        libdirs {
            "%{LibraryDir.SDL_Debug}",
            "%{LibraryDir.ENet_Debug}"
        }
        links {
            "SDL3", "enet", "ws2_32", "winmm"
        }

    filter "configurations:Release"
        runtime "Release"
        libdirs {
            "%{LibraryDir.SDL_Release}",
            "%{LibraryDir.ENet_Release}"
        }
        links {
            "SDL3", "enet", "ws2_32", "winmm"
        }

    filter {}

project "Game"
    location "Game"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"            -- Use dynamic CRT (/MD)

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Game/**.h",
        "Game/**.cpp"
    }
	
	    includedirs {
        "Engine",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.ENet}",
        "%{IncludeDir.stb}"
    }

    links {
        "Engine"
    }

    dependson {
        "Engine"
    }
	
	    filter "configurations:Debug"
        runtime "Debug"
        postbuildcommands {
            'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        runtime "Release"
        postbuildcommands {
            'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
        }

    filter {}
	
project "Client"
    location "Client"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"            -- Use dynamic CRT (/MD)

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Client/**.h",
        "Client/**.cpp"
    }

    includedirs {
        "Engine",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.ENet}",
        "%{IncludeDir.stb}"
    }

    links {
        "Game"
    }

    dependson {
        "Game"
    }

    filter "configurations:Debug"
        runtime "Debug"
        postbuildcommands {
            'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        runtime "Release"
        postbuildcommands {
            'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
        }

    filter {}

project "Server"
    location "Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"            -- Use dynamic CRT (/MD)

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Server/**.h",
        "Server/**.cpp"
    }

    includedirs {
        "Engine",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.ENet}",
        "%{IncludeDir.stb}"
    }

    links {
        "Game"
    }

    dependson {
        "Game"
    }

    filter "configurations:Debug"
        runtime "Debug"
        postbuildcommands {
            'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        runtime "Release"
        postbuildcommands {
            'cmd /c if exist "..\\extern\\SDL\\install\\bin\\SDL3.dll" copy /Y "..\\extern\\SDL\\install\\bin\\SDL3.dll" "%{cfg.targetdir}"'
        }

    filter {}
