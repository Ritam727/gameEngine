project "obj"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "../",
        "../assimp",
        "../spdlog/include"
    }

    libdirs {
        "../../lib"
    }

    links {
        "imgui",
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
        "-O2",
        "-funroll-loops"
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