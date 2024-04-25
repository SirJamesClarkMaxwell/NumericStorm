project "NumericStorm-Tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    location "%{wks.location}/Tests"
    files {
        "**.cpp",
        "**.hpp",
        "**.h"
    }
    
    libdirs {
        "./../vendor/googletest-main/bin/%{cfg.buildcfg}"
    }
    
    targetdir ("./bin/%{cfg.buildcfg}")
    objdir ("./obj/%{cfg.buildcfg}")
    
    links { 
        "NumericStorm",
        "gtest"
    }

    includedirs { 
        "../NumericStorm/**",
        "../vendor/googletest-main/googletest/**",
        "../vendor/googletest-main/googletest/include/**",
        "../vendor/googletest-main/googletest/include/gtest/**",
        "./**"
    }

    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    