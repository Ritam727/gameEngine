project "engine"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "../vendor/assimp",
        "../vendor/spdlog/include",
        "../vendor",
        "../core",
        "../vendor/glad/include"
    }

    libdirs {
        "../../lib"
    }

    links {
        "glad",
        "glfw",
        "assimp",
        "spdlog"
    }

    defines {
        "PLATFORM_LINUX",
        "SPDLOG_COMPILED_LIB"
    }

    files {
        "**.cpp",
        "**.hpp"
    }
    
    buildoptions {
        "-funroll-loops"
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