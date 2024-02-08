workspace "NumericStorm-App"
    configurations {"Debug","Release"}

dofile "NumericStorm/premake5.lua"
dofile "Tests/premake5.lua"

project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    libdirs {"./vendor/googletest-main/bin/Debug/"}

    files { 
        "./src/*.cpp", 
        "./headers/*.hpp"
    }
    links { 
        "NumericStorm",
        "gtest"
    }
    
    includedirs { 
        "./NumericStorm/headers/",
        "include",
        "headers "

    }
    targetdir ("bin/%{cfg.buildcfg}") 
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
