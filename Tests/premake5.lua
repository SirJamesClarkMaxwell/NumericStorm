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
        "./FittingTests/*.*"
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
            "%{prj.location}/FittingTests"
            }
        targetdir ("bin/%{cfg.buildcfg}") 
    
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
    
    