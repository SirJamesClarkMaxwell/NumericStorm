workspace "VendorCompilingProject"
    configurations {"Debug","Release"}

    dofile "googletest-main/premake5.lua"

    project "App"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"

        targetdir ("bin/%{cfg.buildcfg}") 
    includedirs{
        "googletest-main/googletest/include/",
    }
    files{

        "*.h",
        "*.hpp",
        "*.cpp",
        "*.cc"
    }

    links {
        "gtest"
    }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"