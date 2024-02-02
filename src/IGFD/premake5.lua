project "IGFD"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    libdirs {
        "../../lib"
    }

    includedirs {
        "../"
    }

    files {
        "*.cpp"
    }

    links {
        "imgui"
    }

    buildoptions {
        "-funroll-loops"
    }

    filter "configurations:Release"
        defines {
            "LOGGER_WARN",
            "ENVIRONMENT_DEBUG"
        }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always",
            "-O2"
        }

        defines {
            "LOGGER_DEBUG",
            "ENVIRONMENT_DEBUG"
        }

        symbols "On"