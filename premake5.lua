outputdir = "bin/%{cfg.buildcfg}/%{cfg.architecture}"

LocalFiles = {
	Public = "%{prj.location}/src/public",
	Private = "%{prj.location}/src/private"
}

ExternalDLLDir = {
	SDL = "Externals/SDL3/lib/x64" 	-- Fix this if support for other architectures is added
}

ExternalIncludeDir = {
	SDL = "Externals/SDL3/include",
	enet = "Externals/enet/include"
}

workspace "OnlineGame"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

project "Engine"
	location "Source/%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	(outputdir .. "/bin/%{prj.name}")
	objdir		(outputdir .. "/obj/%{prj.name}")

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
		"Externals/SDL3/lib/x64", 	-- Fix this if support for other architectures is added
		"Externals/enet"
	}

	links {
		"SDL3",
		"enet",
		"enet64",
		"ws2_32",
		"winmm"
	}

project "Game"
	location "Source/%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	(outputdir .. "/bin/%{prj.name}")
	objdir		(outputdir .. "/obj/%{prj.name}")

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

project "Server"
	location "Source/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	(outputdir .. "/bin/%{prj.name}")
	objdir		(outputdir .. "/obj/%{prj.name}")

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
		"Source/Game/src/public"
	}

	links {
		"Game"
	}

	dependson {
		"Game"
	}

	postbuildcommands {
		ok, err = os.copyfile("%{ExternalDLLDir.SDL}", "%{prj.location}")
	}

project "Client"
	location "Source/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	systemversion "latest"
	staticruntime "on"

	targetdir	(outputdir .. "/bin/%{prj.name}")
	objdir		(outputdir .. "/obj/%{prj.name}")

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
		"Source/Game/src/public"
	}

	links {
		"Game"
	}

	dependson {
		"Game"
	}

	postbuildcommands {
		ok, err = os.copyfile("%{ExternalDLLDir.SDL}", "%{prj.location}")
	}