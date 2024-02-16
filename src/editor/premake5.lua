include "../core"

project "editor"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "../editor",
        "../vendor",
        "../core",
        "../vendor/spdlog/include",
        "../vendor/glad/include"
    }

    libdirs {
        "../../lib"
    }

    links {
        "glfw",
        "core"
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