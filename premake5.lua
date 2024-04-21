workspace "ZArchive"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ZArchive"
	location "ZArchive"
	kind "StaticLib"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		--"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZA_BUILD_DLL",
			"ZA_PLATFORM_WINDOWS",
			"_WINDLL",
			"_UNICODE",
			"UNICODE",
		}

		postbuildcommands
		{
			--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "ZA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZA_DIST"
		runtime "Release"
		optimize "on"

project "ZArchiveTest"
	location "ZArchiveTest"
	kind "ConsoleApp"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		--"Hazel/vendor/spdlog/include",
		"ZArchive/src"
	}

	links
	{
		"ZArchive"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZA_PLATFORM_WINDOWS",
			"_UNICODE",
			"UNICODE",
		}

	filter "configurations:Debug"
		defines "ZA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZA_DIST"
		runtime "Release"
		optimize "on"