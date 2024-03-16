-- dofile "/vendor/googletest-main/premake5.lua"
--dofile "../NumericStorm/premake5.lua"


project "NumericStorm-Tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    location "%{wks.location}/Tests"
    files {
        "*.cpp",
        "*.h",
        "*.hpp",
        "../NumericStorm/headers/*.hpp",
        "./FittingTests/*.*",
        "./FittingTests/Nealder-Mead-Tests/*.*",
        "./FittingTests/Nealder-Mead-Tests/SimplexOperation-Test/*.*"
    }
    
        libdirs{
            "../vendor/googletest-main/bin/Debug/"}
        
        targetdir ("bin/%{cfg.buildcfg}")
        objdir ("obj/%{cfg.buildcfg}")
    
        links { 
        "NumericStorm",
        "gtest"
            }
        includedirs { 
            "../NumericStorm/headers/",
            "../vendor/googletest-main/googletest/include/" ,
            "../vendor/googletest-main/googletest/include/gtest",
            "%{prj.location}/FittingTests",
            "%{prj.location}/FittingTests/Nealder-Mead-Tests",
            "%{prj.location}/FittingTests/Nealder-Mead-Tests/SimplexOperation-Test"
            }
        targetdir ("bin/%{cfg.buildcfg}") 
    
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
    
    