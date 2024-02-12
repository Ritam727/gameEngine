project "obj"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "../assimp",
        "../spdlog/include",
        "../",
        "../include",
        "../glad/include/"
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