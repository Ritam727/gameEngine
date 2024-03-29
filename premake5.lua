workspace "LearnOpenGL"
    configurations { "Debug", "Release" }

group "dependencies"
    include "src/glad"
    include "src/include"
    include "src/IGFD"
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
        "src/",
        "src/assimp",
        "src/spdlog/include",
        "src/glad/include"
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
        "spdlog",
        "IGFD"
    }

    defines {
        "PLATFORM_LINUX",
        "SPDLOG_COMPILED_LIB"
    }

    buildoptions {
        "-funroll-loops"
    }

    filter "system:Linux"
        links {
            "X11"
        }
    
    filter "configurations:Release"
        defines {
            "LOGGER_WARN",
            "ENVIRONMENT_DEBUG"
        }

        buildoptions {
            "-O2"
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