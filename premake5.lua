workspace "LearnOpenGL"
    configurations { "Debug", "Release" }

group "dependencies"
    include "src/glad"
    include "src/include"
group ""

project "main"
    kind "ConsoleApp"
    language "C++"

    targetdir ""
    objdir "objects"

    files {
        "src/*.cpp"
    }

    includedirs {
        "src/include",
        "src/include/**",
        "src/",
        "src/assimp",
        "src/spdlog/include"
    }

    libdirs { 
        "lib"
    }

    links {
        "imgui",
        "glfw",
        "obj",
        "glad",
        "assimp",
        "spdlog"
    }

    defines {
        "PLATFORM_LINUX",
        "SPDLOG_COMPILED_LIB"
    }

    buildoptions {
        "-O2",
        "-funroll-loops"
    }

    filter "system:Linux"
        links {
            "X11"
        }
    
    filter "configurations:Release"
        defines {
            "LOGGER_WARN"
        }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }

        defines {
            "LOGGER_DEBUG",
            "ENVIRONMENT_DEBUG"
        }

        symbols "On"