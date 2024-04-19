project "NumericStorm-Tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    location "%{wks.location}/Tests"
    files {
        "**.cpp",
        "**.hpp"
    }
    
        libdirs {
            "../vendor/googletest-main/bin/%{cfg.buildcfg}"
        }
        
        targetdir ("./bin/%{cfg.buildcfg}")
        objdir ("./obj/%{cfg.buildcfg}")
    
        links { 
            "NumericStorm",
            "gtest"
        }

        includedirs { 
            "../NumericStorm/headers/**",
            "../vendor/googletest-main/googletest/include/**" ,
            "./FittingTests/**"
         }

    
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
    
    