outputdir = "%{cfg.buildcfg}/%{cfg.architecture}"

LocalFiles = {
	Public = "%{prj.location}/src/public",
	Private = "%{prj.location}/src/private"
}

ExternalIncludeDir = {
	SDL = "Externals/SDL3/include",
	enet = "Externals/enet/include"
}

workspace "OnlineGame"
	architecture "x64"
	configurations { "Debug", "Release" }

project "Engine"
	location "Source/%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	("Binaries/bin/" .. outputdir .. "/%{prj.name}")
	objdir		("Binaries/obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"%{LocalFiles.Public}",
		"%{LocalFiles.Prive}",
		"%{ExternalIncludeDir.SDL}",
		"%{ExternalIncludeDir.enet}"
	}

	libdirs {
		"Externals/SDL3/lib/x64",
		"Externals/enet"
	}

	links {
		"SDL3",
		"enet",
		"enet64",
		"ws2_32",
		"winmm"
	}

	filter "configurations:Debug"
        symbols "on"
		optimize "off"

	filter "configurations:Release"
		symbols "off"
        optimize "on"

project "Game"
	location "Source/Demos/ClientServerGame/%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	("Binaries/bin/" .. outputdir .. "/Demos/ClientServerGame/%{prj.name}")
	objdir		("Binaries/obj/" .. outputdir .. "/Demos/ClientServerGame/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"%{LocalFiles.Public}",
		"%{LocalFiles.Prive}",
		"%{ExternalIncludeDir.SDL}",
		"%{ExternalIncludeDir.enet}",
		"Source/Engine/src/public"
	}

	links {
		"Engine"
	}

	dependson {
		"Engine"
	}

	filter "configurations:Debug"
        symbols "on"
		optimize "off"

	filter "configurations:Release"
		symbols "off"
        optimize "on"

project "Server"
	location "Source/Demos/ClientServerGame/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	("Binaries/bin/" .. outputdir .. "/Demos/ClientServerGame/%{prj.name}")
	objdir		("Binaries/obj/" .. outputdir .. "/Demos/ClientServerGame/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"%{LocalFiles.Public}",
		"%{LocalFiles.Prive}",
		"%{ExternalIncludeDir.SDL}",
		"%{ExternalIncludeDir.enet}",
		"Source/Engine/src/public",
		"Source/Demos/ClientServerGame/Game/src/public"
	}

	links {
		"Game"
	}

	dependson {
		"Game"
	}

	filter "configurations:Debug"
        symbols "on"
		optimize "off"

	filter "configurations:Release"
		symbols "off"
        optimize "on"

project "Client"
	location "Source/Demos/ClientServerGame/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	("Binaries/bin/" .. outputdir .. "/Demos/ClientServerGame/%{prj.name}")
	objdir		("Binaries/obj/" .. outputdir .. "/Demos/ClientServerGame/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"%{LocalFiles.Public}",
		"%{LocalFiles.Prive}",
		"%{ExternalIncludeDir.SDL}",
		"%{ExternalIncludeDir.enet}",
		"Source/Engine/src/public",
		"Source/Demos/ClientServerGame/Game/src/public"
	}

	links {
		"Game"
	}

	dependson {
		"Game"
	}

	postbuildcommands {
		'cmd /c if exist "..\\..\\..\\..\\Externals\\SDL3\\lib\\x64\\SDL3.dll" copy /Y "..\\..\\..\\..\\Externals\\SDL3\\lib\\x64\\SDL3.dll" "%{cfg.targetdir}"'
	}

	filter "configurations:Debug"
        symbols "on"
		optimize "off"

	filter "configurations:Release"
		symbols "off"
        optimize "on"

project "jNetTestBed"
	location "Source/Demos/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	("Binaries/bin/" .. outputdir .. "/Demos/%{prj.name}")
	objdir		("Binaries/obj/" .. outputdir .. "/Demos/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"%{LocalFiles.Public}",
		"%{LocalFiles.Prive}",
		"Source/Engine/src/public"
	}

	links {
		"Engine"
	}

	dependson {
		"Engine"
	}

	filter "configurations:Debug"
        symbols "on"
		optimize "off"

	filter "configurations:Release"
		symbols "off"
        optimize "on"