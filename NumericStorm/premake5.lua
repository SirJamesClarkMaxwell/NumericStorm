project "NumericStorm"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    -- Source files
    files { 
        "src/*.cpp",
        "headers/*.hpp",
         }

    -- Header files
    includedirs { 
        "./headers",
        "./src" }

    -- Output directory for the generated library
    targetdir ("bin/%{cfg.buildcfg}")

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
