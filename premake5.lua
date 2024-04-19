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
            "./src/**.cpp", 
            "./headers/**.hpp",
            "./NumericStorm/**.hpp",
            "./NumericStorm/**.cpp"
        }
        links { 
            "NumericStorm",
            "gtest"
        }
        
        includedirs { 
            "./NumericStorm/**"
        }
        targetdir ("./bin/%{cfg.buildcfg}") 
        
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
    