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
        "./headers/*.hpp",
        "./NumericStorm/headers/*.hpp",
        "./NumericStorm/headers/Fitting/*.hpp",
        "./NumericStorm/headers/Fitting/Exceptions/*.hpp",
        "./NumericStorm/headers/Fitting/Nealder-Mead/*.hpp",
        "./NumericStorm/headers/Fitting/Nealer-Mead/SimplexOperations/*.hpp",
        "./NumericStorm/headers/Fitting/Nealder-Mead/BasicSimplex/*.hpp",
        "./NumericStorm/headers/Fitting/Nealder-Mead/SimplexCreator/*.hpp"
    }
    links { 
        "NumericStorm",
        "gtest"
    }
    
    includedirs { 
        "include",
        "headers",
        "./NumericStorm/headers/",
        "./NumericStorm/headers/Fitting/",
        "./NumericStorm/headers/Fitting/Exceptions/",
        "./NumericStorm/headers/Fitting/Nealder-Mead/",
        "./NumericStorm/headers/Fitting/Nealer-Mead/SimplexOperations/",
        "./NumericStorm/headers/Fitting/Nealder-Mead/BasicSimplex/",
        "./NumericStorm/headers/Fitting/Nealder-Mead/SimplexCreatorp"

    }
    targetdir ("bin/%{cfg.buildcfg}") 
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
