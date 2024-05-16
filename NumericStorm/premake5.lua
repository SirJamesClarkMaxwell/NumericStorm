project "NumericStorm"
	kind "StaticLib"
	language "C++"
	cppdialect "c++latest"
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
