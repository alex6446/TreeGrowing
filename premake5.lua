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

	includedirs {
		"vendor",
		"vendor/ImGUI",
		"TreeGrowing/include",
		"NodelEditor/include",
		"TreeGrowing/src"
	}
	--flags "RelativeLinks"

	links {
		"sfml-graphics", "sfml-window", "sfml-system", "GL", "thor"
	}

	libdirs { "libs" }
	linkoptions{ "-Wl,-rpath=libs" }

	configuration { "linux" }
  		buildoptions { "-std=c++17" }

  	postbuildcommands {
  		("{COPY} libs/%{cfg.system} %{cfg.buildtarget.directory}/libs"),
  		("{COPY} assets %{cfg.buildtarget.directory}")
  	}

   	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"