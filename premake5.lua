workspace "LearnOpenGL"
    configurations { "Debug", "Release" }

group "dependencies"
    include "src/vendor/glad"
    include "src/vendor/IGFD"
    include "src/editor"
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
        "src/",
        "src/core",
        "src/vendor",
        "src/vendor/assimp",
        "src/vendor/spdlog/include",
        "src/vendor/glad/include"
    }

    libdirs { 
        "lib"
    }

    links {
        "imgui",
        "glfw",
        "core",
        "glad",
        "assimp",
        "spdlog",
        "IGFD",
        "editor"
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