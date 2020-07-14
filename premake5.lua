workspace "Oasis"
	architecture "x64"

configurations{
	"Debug",
	"Release",
	"Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Oasis"
	location "Oasis"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs{
		"%{prj.name}/src",
		"Oasis/src/Oasis/Events",
	  "%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
		 "OE_PLATFORM_WINDOWS",
		 "OE_BUILD_DLL"
		}
		
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OE_RELEASE"
		optimize "On"
     
	 filter "configurations:Dist"
		defines "OE_DIST"
		optimize "On"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs{
	  "Oasis/vendor/spdlog/include",
	  "Oasis/src",
	  "Oasis/src/Oasis/Events"
	}
	links{
		"Oasis"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
		 "OE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OE_RELEASE"
		optimize "On"
     
	 filter "configurations:Dist"
		defines "OE_DIST"
		optimize "On"
