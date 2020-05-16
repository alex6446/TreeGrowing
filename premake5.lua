workspace "TreeGrowing"
	architecture "x86_64"
	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "TreeGrowing"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir)
	objdir ("obj/" .. outputdir)

	files { 
		"TreeGrowing/src/**.h", 
		"TreeGrowing/src/**.cpp", 
		"ModelEditor/src/**.h", 
		"ModelEditor/src/**.cpp", 
		"Application/src/**.cpp", 
		"vendor/**.h",
		"vendor/**.cpp"
	}
	
	defines { "_USE_MATH_DEFINES" }

	includedirs {
		"vendor",
		"vendor/ImGUI",
		"TreeGrowing/include",
		"NodelEditor/include",
		"TreeGrowing/src"
	}
	--flags "RelativeLinks"

	links {
		"sfml-graphics", "sfml-window", "sfml-system", "thor"
	}

	libdirs { "libs/%{cfg.system}" }

	postbuildcommands {
		("{COPY} assets %{cfg.buildtarget.directory}/assets")
	}

	configuration { "linux" }
		links { "GL" }
		linkoptions{ "-Wl,-rpath=libs" }
  		buildoptions { "-std=c++17" }
		postbuildcommands {
			("{COPY} libs/%{cfg.system}/. %{cfg.buildtarget.directory}/libs")
		}
		
	configuration { "windows" }
		links { "opengl32" }
		postbuildcommands {
			("{COPY} libs/%{cfg.system}/**.dll %{cfg.buildtarget.directory}")
		}

   	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"