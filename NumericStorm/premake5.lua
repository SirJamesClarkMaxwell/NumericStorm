project "NumericStorm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	location "%{wks.location}/NumericStorm"

	
	files { 
		"**.cpp",
		"**.hpp"
	}

	includedirs { 
		"./headers/**"
	}

	targetdir ("./bin/%{cfg.buildcfg}")

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
