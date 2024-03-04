workspace "NumericStorm-App"
    configurations {"Debug","Release"}
    location "./"

    include("./NumericStorm/premake5.lua")
    include("./Tests/premake5.lua")
    
    project "App"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        location "%{wks.location}"
    
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
            "./NumericStorm/headers/Fitting/Nealder-Mead/SimplexCreator/*.hpp",
            "./headers/Fitting/Nealder-Mead/SimplexDecision/*.hpp"
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
            "./NumericStorm/headers/Fitting/Nealder-Mead/SimplexCreatorp",
            "./headers/Fitting/Nealder-Mead/SimplexDecision/"
            
        }
        targetdir ("bin/%{cfg.buildcfg}") 
        
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
    