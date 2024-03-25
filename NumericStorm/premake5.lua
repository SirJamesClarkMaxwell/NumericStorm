project "NumericStorm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	-- Source files
	files { 
		"*.cpp",
		"*.h",
		"*.hpp",
		"src/*.cpp",
		"src/Fitting/*.cpp",
		"./headers/*.hpp",
		"./headers/Fitting/*.hpp",
		"./headers/Fitting/Exceptions/*.hpp",
		"./headers/Fitting/Nealder-Mead/*.hpp",
		"./headers/Fitting/Nealder-Mead/SimplexCreator/*.hpp",
		"./headers/Fitting/Nealder-Mead/SimplexOperations/*.hpp",
		"./headers/Fitting/Nealder-Mead/SimplexDecision/*.hpp",
		"./headers/Fitting/Nealder-Mead/BasicSimplex/*.hpp"
	}

	-- Header files
	includedirs { 
		"./headers",
		"./headers/Fitting/Exceptions/",
		"./headers/Fitting/Nealder-Mead/",
		"./headers/Fitting/Nealder-Mead/SimplexOperations/",
		"./headers/Fitting/Nealder-Mead/SimplexCreator/",
		"./headers/Fitting/Nealder-Mead/SimplexDecision/",
		"./headers/Fitting/Nealder-Mead/BasicSimplex/",
		"./src" }

	-- Output directory for the generated library
	targetdir ("bin/%{cfg.buildcfg}")

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
